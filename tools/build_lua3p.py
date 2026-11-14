"""build_lua3p - build AiLive's native libraries from pinned upstream and first-party sources (#842, #854).

Ken, 2026-10-26: our own DLLs, built by us, from upstream - no third party's binaries in the mod.

What it produces in ../x4_AiLive-build/lua3p/ (staging only; deployment is separate):
  luasocket/core.dll   LuaSocket v3.1.0 C core, compiled here with MSVC, linked to X4's own lua51_64.dll (LuaJIT 2.1)
  luasocket/socket.lua LuaSocket v3.1.0 src/socket.lua, verbatim
  json.lua             rxi/json.lua, verbatim
  cjson/cjson.dll       private card codec, unpatched OpenResty lua-cjson 2.1.0.19
  aickeys/aickeys.dll   first-party foreground-only allowlisted key polling
  BUILD.md             where every input came from (URL, commit, sha256), the compiler and the flags

Everything is fetched from the original projects at pinned commits and checked against a pinned sha256 before use.
Nothing here is run from a download: sources are compiled, and the Lua files are copied. Python standard library only.

usage: python tools/build_lua3p.py [--x4 "G:/SteamLibrary/steamapps/common/X4 Foundations"] [--cache DIR] [--out STAGING_DIR]
"""
import argparse, hashlib, os, re, shutil, struct, subprocess, tarfile, tempfile, urllib.request
from pathlib import Path, PurePosixPath

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# pinned inputs: (url, sha256) - the commit is in the URL; the sha256 is of the downloaded bytes
LUASOCKET = ('https://github.com/lunarmodules/luasocket/archive/95b7efa9da506ef968c1347edf3fc56370f0deed.tar.gz', None)   # tag v3.1.0
LUAJIT = ('https://github.com/LuaJIT/LuaJIT/archive/a4c064539ea931274d407e1249b4bb575424a0f4.tar.gz', None)               # headers only (Lua 5.1 C API)
RXI_JSON = ('https://raw.githubusercontent.com/rxi/json.lua/dbf4b2dd2eb7c23be2773c89eb059dadd6436f94/json.lua', None)
RXI_LICENSE = ('https://raw.githubusercontent.com/rxi/json.lua/dbf4b2dd2eb7c23be2773c89eb059dadd6436f94/LICENSE', None)
CJSON = ('https://github.com/openresty/lua-cjson/archive/5ce46a80b10ef9d380a45c9e6cff9ecffbe71ebb.tar.gz', None)
PINS_FILE = os.path.join(ROOT, 'tools', 'lua3p_pins.txt')   # reviewed pins; never written by the build
INPUTS = (LUASOCKET, LUAJIT, RXI_JSON, RXI_LICENSE, CJSON)
SDK_VERSION = '10.0.26100.0'
MSVC_VERSION = '14.44'
LINK_FLAGS = ['/NOLOGO', '/DLL', '/INCREMENTAL:NO', '/OPT:REF', '/OPT:ICF']


def compiler_environment():
    # MSVC consumes these variables before/after the command line; they are not build inputs.
    return {k: v for k, v in os.environ.items() if k.upper() not in ('CL', '_CL_', 'LINK', '_LINK_')}

SOCKET_SRC = ['luasocket.c', 'timeout.c', 'buffer.c', 'io.c', 'auxiliar.c', 'compat.c', 'options.c', 'inet.c', 'wsocket.c',
              'except.c', 'select.c', 'tcp.c', 'udp.c']   # upstream makefile SOCKET_OBJS for Windows
# upstream DEF_win64 / CFLAGS_win64, with /MT (static C runtime: the DLL needs no Visual C++ runtime installed) instead of /MD
CL_FLAGS = ['/nologo', '/O2', '/Ot', '/MT', '/W3', '/DWIN32', '/DNDEBUG', '/D_WINDOWS', '/D_USRDLL', '/D_CRT_SECURE_NO_WARNINGS',
            '/D_WINDLL', '/DLUASOCKET_NODEBUG', '/DLUASOCKET_API=__declspec(dllexport)']
CJSON_SRC = ['lua_cjson.c', 'strbuf.c', 'g_fmt.c', 'dtoa.c']
CJSON_FLAGS = ['/nologo', '/O2', '/MT', '/W3', '/DUSE_INTERNAL_FPCONV', '/DNDEBUG',
               '/D_CRT_SECURE_NO_WARNINGS', '/DCJSON_VERSION="2.1.0.19"']
AICKEYS_FLAGS = ['/nologo', '/O2', '/MT', '/W4', '/WX', '/DWIN32', '/DNDEBUG',
                '/D_WINDOWS', '/D_USRDLL', '/D_WINDLL']


def copyright_notices(path):
    """Preserve complete copyright/permission comments, even after a provenance comment."""
    text = Path(path).read_text(encoding='utf-8')
    notices = [m.group(0) for m in re.finditer(r'/\*.*?\*/', text, re.DOTALL)
               if 'copyright' in m.group(0).lower() and 'permission' in m.group(0).lower()]
    if not notices:
        raise SystemExit('expected upstream copyright/permission notice: ' + str(path))
    return '\n\n'.join(notices)


def module_commands(inc, socket_src, cjson_src, aickeys_src, link_flags):
    """Arguments go through response files, never shell interpolation."""
    return {
        'core': CL_FLAGS + ['/I' + inc, '/I' + socket_src, '/Fe:core.dll', '/LD']
                + [os.path.join(socket_src, c) for c in SOCKET_SRC]
                + ['/link'] + link_flags + ['lua51_64.lib', 'ws2_32.lib'],
        'cjson': CJSON_FLAGS + ['/I' + inc, '/I' + cjson_src, '/Fe:cjson.dll', '/LD']
                 + [os.path.join(cjson_src, c) for c in CJSON_SRC]
                 + ['/link'] + link_flags + ['lua51_64.lib'],
        'aickeys': AICKEYS_FLAGS + ['/I' + inc, '/Fe:aickeys.dll', '/LD', aickeys_src]
                   + ['/link'] + link_flags + ['lua51_64.lib', 'user32.lib'],
    }


def log(m): print('[build_lua3p] ' + m, flush=True)


def pins():
    out = {}
    with open(PINS_FILE, encoding='utf-8') as f:
        for number, line in enumerate(f, 1):
            if not line.strip() or line.lstrip().startswith('#'):
                continue
            parts = line.split()
            if len(parts) != 2 or not re.fullmatch(r'[0-9a-f]{64}', parts[1]) or parts[0] in out:
                raise SystemExit('invalid or duplicate pin at line %d' % number)
            out[parts[0]] = parts[1]
    for url, _ in INPUTS:
        if url not in out:
            raise SystemExit('MISSING SHA256 PIN for ' + url)
    return out


def fetch(url, cache, pinned):
    if url not in pinned:
        raise SystemExit('MISSING SHA256 PIN for ' + url)
    name = hashlib.sha1(url.encode()).hexdigest()[:12] + '_' + url.rsplit('/', 1)[-1]
    path = os.path.join(cache, name)
    if not os.path.isfile(path):
        log('download ' + url)
        with urllib.request.urlopen(url, timeout=60) as r:
            data = r.read()
        h = hashlib.sha256(data).hexdigest()
        if h != pinned[url]:
            raise SystemExit('SHA256 MISMATCH for %s: got %s, pinned %s' % (url, h, pinned[url]))
        with open(path, 'wb') as f:
            f.write(data)
    with open(path, 'rb') as f:
        data = f.read()
    h = hashlib.sha256(data).hexdigest()
    if len(data) < 200:
        raise SystemExit('download failed (%d bytes): %s' % (len(data), url))
    if pinned[url] != h:
        raise SystemExit('SHA256 MISMATCH for %s: got %s, pinned %s' % (url, h, pinned[url]))
    return path, h


def safe_extract(tgz, dest):
    # Strip the archive's long commit-named root BEFORE extraction, including on Windows.
    short = Path(dest).resolve() / 's'
    members = []
    roots = set()
    with tarfile.open(tgz, 'r:gz') as t:
        for m in t.getmembers():
            parts = PurePosixPath(m.name).parts
            if (not parts or m.name.startswith('/') or '\\' in m.name or ':' in m.name
                    or '..' in parts or not (m.isfile() or m.isdir())):
                raise SystemExit('unsafe archive member: ' + m.name)
            roots.add(parts[0])
            target = short.joinpath(*parts[1:]).resolve()
            if not target.is_relative_to(short) or (len(parts) == 1 and not m.isdir()):
                raise SystemExit('unsafe archive member: ' + m.name)
            members.append((m, target))
        if len(roots) != 1:
            raise SystemExit('archive must have exactly one source root')
        for member, target in members:
            if member.isdir():
                target.mkdir(parents=True, exist_ok=True)
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                with t.extractfile(member) as source, target.open('wb') as output:
                    shutil.copyfileobj(source, output)
    return str(short)


def dll_exports(path):
    """the export names of a PE DLL (X4's lua51_64.dll) - read from its export directory"""
    b = open(path, 'rb').read()
    if b[:2] != b'MZ':
        raise ValueError('not a PE file')
    pe = struct.unpack_from('<I', b, 0x3c)[0]
    if b[pe:pe + 4] != b'PE\0\0' or struct.unpack_from('<H', b, pe + 4)[0] != 0x8664:
        raise ValueError('expected an x64 PE DLL')
    nsec = struct.unpack_from('<H', b, pe + 6)[0]; optsz = struct.unpack_from('<H', b, pe + 20)[0]
    opt = pe + 24
    if struct.unpack_from('<H', b, opt)[0] != 0x20b:
        raise ValueError('expected a PE32+ optional header')
    exp_rva = struct.unpack_from('<I', b, opt + 112)[0]   # PE32+ data directory 0 = exports
    secs = []
    for i in range(nsec):
        s = pe + 24 + optsz + i * 40
        vsize, va, rsize, rptr = struct.unpack_from('<IIII', b, s + 8)
        secs.append((va, max(vsize, rsize), rptr))
    def off(rva):
        for va, size, rptr in secs:
            if va <= rva < va + size: return rva - va + rptr
        raise ValueError('rva not mapped')
    e = off(exp_rva)
    n_names = struct.unpack_from('<I', b, e + 24)[0]; names_rva = struct.unpack_from('<I', b, e + 32)[0]
    out = []
    for i in range(n_names):
        nrva = struct.unpack_from('<I', b, off(names_rva) + 4 * i)[0]
        o = off(nrva); out.append(b[o:b.index(b'\0', o)].decode())
    return out


def vcvars():
    preferred = r'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat'
    if os.path.isfile(preferred):
        return preferred
    vswhere = os.path.join(os.environ.get('ProgramFiles(x86)', r'C:\Program Files (x86)'), 'Microsoft Visual Studio', 'Installer', 'vswhere.exe')
    paths = subprocess.run([vswhere, '-all', '-products', '*', '-requires', 'Microsoft.VisualStudio.Component.VC.Tools.x86.x64',
                            '-property', 'installationPath'], capture_output=True, text=True, check=True).stdout.splitlines()
    for p in paths:
        v = os.path.join(p.strip(), 'VC', 'Auxiliary', 'Build', 'vcvars64.bat')
        if os.path.isfile(v): return v
    raise SystemExit('no MSVC x64 toolchain found (vcvars64.bat)')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--x4', default=r'G:\SteamLibrary\steamapps\common\X4 Foundations')
    ap.add_argument('--cache', default=os.path.join(tempfile.gettempdir(), 'aicb', 'c'))
    ap.add_argument('--work-root', default=os.path.join(tempfile.gettempdir(), 'aicb'))
    ap.add_argument('--out', default=os.path.join(os.path.dirname(ROOT), 'x4_AiLive-build', 'lua3p'))
    ap.add_argument('--no-brepro', action='store_true', help='omit the optional deterministic linker flag')
    a = ap.parse_args()
    out = Path(a.out).resolve()
    if out == (Path(ROOT) / 'lua3p').resolve() or out.is_relative_to(Path(a.x4).resolve()):
        raise SystemExit('--out must be a staging directory, not the source/live lua3p')
    expected = {'luasocket/core.dll', 'luasocket/socket.lua', 'json.lua', 'LICENSE-LuaSocket.txt',
                'LICENSE-json.lua.txt', 'BUILD.md', 'THIRD_PARTY_LICENSES.md',
                'cjson/cjson.dll', 'aickeys/aickeys.dll', 'LICENSE-lua-cjson.txt'}
    if out.exists():
        extras = {p.relative_to(out).as_posix() for p in out.rglob('*') if p.is_file()} - expected
        if extras:
            raise SystemExit('staging output contains unexpected files: ' + ', '.join(sorted(extras)))
    lua_dll = os.path.join(a.x4, 'lua51_64.dll')
    if not os.path.isfile(lua_dll): raise SystemExit('X4 lua51_64.dll not found at ' + lua_dll)
    os.makedirs(a.cache, exist_ok=True)
    os.makedirs(a.work_root, exist_ok=True)
    pinned = pins()
    ls_tgz, ls_h = fetch(LUASOCKET[0], a.cache, pinned)
    lj_tgz, lj_h = fetch(LUAJIT[0], a.cache, pinned)
    js, js_h = fetch(RXI_JSON[0], a.cache, pinned)
    jl, jl_h = fetch(RXI_LICENSE[0], a.cache, pinned)
    cj_tgz, cj_h = fetch(CJSON[0], a.cache, pinned)
    work = tempfile.mkdtemp(prefix='w', dir=a.work_root)
    log('work: ' + work)
    ls_dir = safe_extract(ls_tgz, os.path.join(work, 'a'))
    lj_dir = safe_extract(lj_tgz, os.path.join(work, 'b'))
    cj_dir = safe_extract(cj_tgz, os.path.join(work, 'c'))
    # Freeze the first-party input alongside the pinned upstream sources for this invocation.
    aickeys_original = Path(ROOT, 'native', 'aickeys', 'aickeys.c')
    aickeys_source = Path(work, 'aickeys.c')
    shutil.copyfile(aickeys_original, aickeys_source)
    aickeys_sha = hashlib.sha256(aickeys_source.read_bytes()).hexdigest()
    inc = os.path.join(work, 'i'); os.makedirs(inc)
    for h in ('lua.h', 'luaconf.h', 'lauxlib.h', 'lualib.h'):
        shutil.copy(os.path.join(lj_dir, 'src', h), inc)

    # an import library for X4's own Lua (the DLL the game loads) - the symbols come from the game's DLL itself
    exports = dll_exports(lua_dll)
    if 'luaL_register' not in exports or 'lua_pushcclosure' not in exports:
        raise SystemExit('lua51_64.dll does not export the Lua 5.1 C API')
    with open(os.path.join(work, 'lua51_64.def'), 'w') as f:
        f.write('LIBRARY lua51_64\nEXPORTS\n' + ''.join('  %s\n' % n for n in exports))

    src = os.path.join(ls_dir, 'src')
    link_flags = LINK_FLAGS + ([] if a.no_brepro else ['/Brepro'])
    commands = module_commands(inc, src, cj_dir, str(aickeys_source), link_flags)
    for module, compile_args in commands.items():
        with open(os.path.join(work, module + '.rsp'), 'w', encoding='utf-8') as f:
            # cl's /link consumes the rest of this LINE; newlines send options back to cl.
            f.write(subprocess.list2cmdline(compile_args) + '\n')
    toolchain = vcvars()
    bat = os.path.join(work, 'build.bat')
    with open(bat, 'w', newline='') as f:
        f.write('@echo off\r\nsetlocal\r\ncall "%s" %s -vcvars_ver=%s >nul\r\nif errorlevel 1 exit /b 1\r\n'
                % (toolchain, SDK_VERSION, MSVC_VERSION))
        f.write('cd /d "%s" || exit /b 1\r\n' % work)
        f.write('lib /nologo /def:lua51_64.def /machine:x64 /out:lua51_64.lib || exit /b 1\r\n')
        for module in commands:
            f.write('cl @%s.rsp || exit /b 1\r\n' % module)
        f.write('cl 2>&1 | findstr /i version > compiler.txt\r\n')
        f.write('link 2>&1 | findstr /i /c:"Linker Version" > linker.txt\r\n')
        f.write('(echo VCToolsVersion=%VCToolsVersion%& echo WindowsSDKVersion=%WindowsSDKVersion%& where cl) > toolchain.txt\r\nexit /b 0\r\n')
    r = subprocess.run(['cmd', '/d', '/c', bat], capture_output=True, text=True, env=compiler_environment())
    Path(work, 'build.log').write_text(r.stdout + '\n' + r.stderr, encoding='utf-8')
    if 'D9002' in r.stdout + r.stderr:
        raise SystemExit('compiler ignored an option; refusing output (see ' + os.path.join(work, 'build.log') + ')')
    if r.returncode != 0 or any(not Path(work, module + '.dll').is_file() for module in commands):
        print(r.stdout[-4000:], r.stderr[-2000:]); raise SystemExit('build failed')
    compiler = open(os.path.join(work, 'compiler.txt'), errors='replace').read().strip()
    linker = Path(work, 'linker.txt').read_text(errors='replace').strip()
    environment = Path(work, 'toolchain.txt').read_text(errors='replace').strip()
    if not compiler or not linker:
        raise SystemExit('compiler/linker version capture failed; see ' + work)

    os.makedirs(os.path.join(out, 'luasocket'), exist_ok=True)
    shutil.copy(os.path.join(work, 'core.dll'), os.path.join(out, 'luasocket', 'core.dll'))
    shutil.copy(os.path.join(src, 'socket.lua'), os.path.join(out, 'luasocket', 'socket.lua'))
    shutil.copy(js, os.path.join(out, 'json.lua'))
    shutil.copy(os.path.join(ls_dir, 'LICENSE'), os.path.join(out, 'LICENSE-LuaSocket.txt'))
    shutil.copy(jl, os.path.join(out, 'LICENSE-json.lua.txt'))
    for module in ('cjson', 'aickeys'):
        (out / module).mkdir(parents=True, exist_ok=True)
        shutil.copy(Path(work, module + '.dll'), out / module / (module + '.dll'))
    shutil.copy(Path(cj_dir, 'LICENSE'), out / 'LICENSE-lua-cjson.txt')
    # Compile-time headers have their own MIT notice; preserve it without shipping the headers.
    luajit_notice = Path(lj_dir, 'COPYRIGHT').read_text(encoding='utf-8')
    third_party = ('# Third-party licenses\n\n'
                   '## LuaSocket\n\nLuaSocket by Diego Nehab and contributors, MIT. '
                   'See LICENSE-LuaSocket.txt (verbatim upstream license).\n\n'
                   '## json.lua\n\njson.lua by rxi, MIT. See LICENSE-json.lua.txt (verbatim upstream license).\n\n'
                   '## LuaJIT headers (compile time only)\n\n'
                   'LuaJIT by Mike Pall and contributors. Only Lua API headers are used to compile the native modules; '
                   'no LuaJIT runtime is distributed here. Runtime Lua is provided by X4.\n\n' + luajit_notice)
    third_party += ('\n\n## lua-cjson\n\nlua-cjson by Mark Pulford, OpenResty fork, MIT. '
                    'See LICENSE-lua-cjson.txt (verbatim upstream license).\n\n'
                    'The internal floating-point conversion sources carry these complete upstream notices.\n')
    for name in ('dtoa.c', 'g_fmt.c'):
        third_party += '\n### ' + name + '\n\n```text\n' + copyright_notices(Path(cj_dir, name)) + '\n```\n'
    Path(out, 'THIRD_PARTY_LICENSES.md').write_text(third_party, encoding='utf-8', newline='\n')
    def h(p): return hashlib.sha256(Path(p).read_bytes()).hexdigest()
    with open(os.path.join(out, 'BUILD.md'), 'w', encoding='utf-8', newline='\n') as f:
        f.write('# How the bundled libraries were built\n\n'
                'Built from pinned original upstream sources by tools/build_lua3p.py (Python standard library only). '
                'Downloaded build scripts and executables are never run.\n\n'
                'Rebuild from the repository root: `python tools/build_lua3p.py`. '
                'This writes ../x4_AiLive-build/lua3p staging output, outside the Forge workspace; '
                'deployment is a separate operation with X4 closed. '
                'Use --x4 for another X4 install and --cache/--work-root for another short build location.\n\n'
                '## Inputs\n\nEvery URL includes its full pinned commit. All download SHA256 values are enforced before use.\n\n'
                '| URL (pinned commit) | Download SHA256 |\n| --- | --- |\n')
        for url, _ in INPUTS:
            f.write('| %s | `%s` |\n' % (url, pinned[url]))
        f.write('\nLuaSocket v3.1.0 supplies the C sources and verbatim socket.lua/license; rxi supplies verbatim '
                'json.lua/license. LuaJIT supplies only lua.h, luaconf.h, lauxlib.h, lualib.h.\n\n'
                'X4 lua51_64.dll SHA256: `%s`; %d named exports used to generate the import library. '
                'No replacement Lua runtime is shipped.\n\n' % (h(lua_dll), len(exports)))
        f.write('First-party source: `native/aickeys/aickeys.c` SHA256 `%s` (copied into the build workspace before compilation).\n\n'
                '## cjson\n\nOpenResty lua-cjson 2.1.0.19, no C patches. Sources: lua_cjson.c, strbuf.c, g_fmt.c, dtoa.c; '
                'fpconv.c and upstream build scripts are not used. Private card codec only; rxi json.lua remains the fallback '
                'and HTTP JSON implementation.\n\n'
                '## aickeys\n\nFirst-party foreground-only allowlisted key polling; no retained state or hooks. '
                'No live keyboard polling is performed by this build. Defender custom-file scan: NOT RUN by the builder; '
                'the handoff must record the scan result and exact aickeys.dll hash before release-candidate acceptance.\n\n'
                % aickeys_sha)
        f.write('## Toolchain and exact build commands\n\nCompiler: %s\n\nLinker: %s\n\n'
                'Environment:\n```text\n%s\n```\n\n' % (compiler, linker, environment))
        f.write('```bat\ncall "%s" %s -vcvars_ver=%s\n'
                'lib /nologo /def:lua51_64.def /machine:x64 /out:lua51_64.lib\n'
                % (toolchain, SDK_VERSION, MSVC_VERSION))
        for compile_args in commands.values():
            f.write('cl %s\n' % subprocess.list2cmdline(compile_args))
        f.write('```\n\nThe commands are passed via core.rsp, cjson.rsp and aickeys.rsp to avoid command-line length limits. '
                'Ambient CL, _CL_, LINK and _LINK_ variables are removed from the compiler subprocess environment. '
                '/MT statically links the C runtime; /Brepro is an optional linker determinism attempt, '
                'not a promise of identical outputs across different compilers or inputs.\n\n'
                '## Outputs\n\n| File | SHA256 |\n| --- | --- |\n')
        for rel in sorted(expected - {'BUILD.md'}):
            f.write('| %s | `%s` |\n' % (rel, h(out / rel)))
        f.write('\nBUILD.md is excluded from its own hash table. Static validation and in-game acceptance '
                'are separate; a successful compile alone does not establish compatibility in X4.\n')
    for rel in ('luasocket/core.dll', 'cjson/cjson.dll', 'aickeys/aickeys.dll'):
        log('built: %s (%d bytes; SHA256 %s)' % (out / rel, (out / rel).stat().st_size, h(out / rel)))
    log('compiler: ' + (compiler or '?'))


if __name__ == '__main__':
    main()
