# How the bundled libraries were built

Built from pinned original upstream sources by tools/build_lua3p.py (Python standard library only). Downloaded build scripts and executables are never run.

Rebuild from the repository root: `python tools/build_lua3p.py`. This writes ../x4_AiLive-build/lua3p staging output, outside the Forge workspace; deployment is a separate operation with X4 closed. Use --x4 for another X4 install and --cache/--work-root for another short build location.

## Inputs

Every URL includes its full pinned commit. All download SHA256 values are enforced before use.

| URL (pinned commit) | Download SHA256 |
| --- | --- |
| https://github.com/lunarmodules/luasocket/archive/95b7efa9da506ef968c1347edf3fc56370f0deed.tar.gz | `076e45e5c7b8e59d2bcda06f0bd4c227b49717f602abe23f7c1e0494fc2fa681` |
| https://github.com/LuaJIT/LuaJIT/archive/a4c064539ea931274d407e1249b4bb575424a0f4.tar.gz | `15625df3ebfbd1f76371005bffae39b84c65e718e57acc9a9c57863c7c101541` |
| https://raw.githubusercontent.com/rxi/json.lua/dbf4b2dd2eb7c23be2773c89eb059dadd6436f94/json.lua | `0eaccda57fabc0330736de25f45cf589821a42b5e0fe02e4e3125f7dc0bf2b7e` |
| https://raw.githubusercontent.com/rxi/json.lua/dbf4b2dd2eb7c23be2773c89eb059dadd6436f94/LICENSE | `e91de14a15c126e70df8d30132529199211b47c5c899f82285a2ee943748f6f2` |
| https://github.com/openresty/lua-cjson/archive/5ce46a80b10ef9d380a45c9e6cff9ecffbe71ebb.tar.gz | `ba78a371233335e1822cede7d2541e88bec77c572ee892e96e87e661153a79f1` |

LuaSocket v3.1.0 supplies the C sources and verbatim socket.lua/license; rxi supplies verbatim json.lua/license. LuaJIT supplies only lua.h, luaconf.h, lauxlib.h, lualib.h.

X4 lua51_64.dll SHA256: `e0712ac93f0d7f3a28236d3153b82e85d35e6bcf8e606af250f664580eaf3b63`; 324 named exports used to generate the import library. No replacement Lua runtime is shipped.

First-party source: `native/aickeys/aickeys.c` SHA256 `a2a73d5ec005884f78ff15fed6df63083bc691acf3bbe3fe59701d4c13b29a5d` (copied into the build workspace before compilation).

## cjson

OpenResty lua-cjson 2.1.0.19, no C patches. Sources: lua_cjson.c, strbuf.c, g_fmt.c, dtoa.c; fpconv.c and upstream build scripts are not used. Private card codec only; rxi json.lua remains the fallback and HTTP JSON implementation.

## aickeys

First-party foreground-only allowlisted key polling; no retained state or hooks. No live keyboard polling is performed by this build. Defender custom-file scan: NOT RUN by the builder; the handoff must record the scan result and exact aickeys.dll hash before release-candidate acceptance.

## Toolchain and exact build commands

Compiler: Microsoft (R) C/C++ Optimizing Compiler Version 19.44.35222 for x64

Linker: Microsoft (R) Incremental Linker Version 14.44.35222.0

Environment:
```text
VCToolsVersion=14.44.35207
WindowsSDKVersion=10.0.26100.0\
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe
```

```bat
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" 10.0.26100.0 -vcvars_ver=14.44
lib /nologo /def:lua51_64.def /machine:x64 /out:lua51_64.lib
cl /nologo /O2 /Ot /MT /W3 /DWIN32 /DNDEBUG /D_WINDOWS /D_USRDLL /D_CRT_SECURE_NO_WARNINGS /D_WINDLL /DLUASOCKET_NODEBUG /DLUASOCKET_API=__declspec(dllexport) /IC:\aicb\wc06zqvd5\i /IC:\aicb\wc06zqvd5\a\s\src /Fe:core.dll /LD C:\aicb\wc06zqvd5\a\s\src\luasocket.c C:\aicb\wc06zqvd5\a\s\src\timeout.c C:\aicb\wc06zqvd5\a\s\src\buffer.c C:\aicb\wc06zqvd5\a\s\src\io.c C:\aicb\wc06zqvd5\a\s\src\auxiliar.c C:\aicb\wc06zqvd5\a\s\src\compat.c C:\aicb\wc06zqvd5\a\s\src\options.c C:\aicb\wc06zqvd5\a\s\src\inet.c C:\aicb\wc06zqvd5\a\s\src\wsocket.c C:\aicb\wc06zqvd5\a\s\src\except.c C:\aicb\wc06zqvd5\a\s\src\select.c C:\aicb\wc06zqvd5\a\s\src\tcp.c C:\aicb\wc06zqvd5\a\s\src\udp.c /link /NOLOGO /DLL /INCREMENTAL:NO /OPT:REF /OPT:ICF /Brepro lua51_64.lib ws2_32.lib
cl /nologo /O2 /MT /W3 /DUSE_INTERNAL_FPCONV /DNDEBUG /D_CRT_SECURE_NO_WARNINGS /DCJSON_VERSION=\"2.1.0.19\" /IC:\aicb\wc06zqvd5\i /IC:\aicb\wc06zqvd5\c\s /Fe:cjson.dll /LD C:\aicb\wc06zqvd5\c\s\lua_cjson.c C:\aicb\wc06zqvd5\c\s\strbuf.c C:\aicb\wc06zqvd5\c\s\g_fmt.c C:\aicb\wc06zqvd5\c\s\dtoa.c /link /NOLOGO /DLL /INCREMENTAL:NO /OPT:REF /OPT:ICF /Brepro lua51_64.lib
cl /nologo /O2 /MT /W4 /WX /DWIN32 /DNDEBUG /D_WINDOWS /D_USRDLL /D_WINDLL /IC:\aicb\wc06zqvd5\i /Fe:aickeys.dll /LD C:\aicb\wc06zqvd5\aickeys.c /link /NOLOGO /DLL /INCREMENTAL:NO /OPT:REF /OPT:ICF /Brepro lua51_64.lib user32.lib
```

The commands are passed via core.rsp, cjson.rsp and aickeys.rsp to avoid command-line length limits. Ambient CL, _CL_, LINK and _LINK_ variables are removed from the compiler subprocess environment. /MT statically links the C runtime; /Brepro is an optional linker determinism attempt, not a promise of identical outputs across different compilers or inputs.

## Outputs

| File | SHA256 |
| --- | --- |
| LICENSE-LuaSocket.txt | `224afe42d0738eaaeb57ab289466a1c4e77091591e69dbcef2dbb385589f2f41` |
| LICENSE-json.lua.txt | `e91de14a15c126e70df8d30132529199211b47c5c899f82285a2ee943748f6f2` |
| LICENSE-lua-cjson.txt | `9576e82ef5013fbe80b3bd446a7d9ddd47328baa2186c31d3d885e2a9a8cd31e` |
| THIRD_PARTY_LICENSES.md | `edb53af4049a23f2bfc680583571a020197b42214c83371c93b4073d3c263edf` |
| aickeys/aickeys.dll | `449931735c7d2c719d085b03a4e90a0cf9b88d5da6aa457ae20f4ac29d68caf7` |
| cjson/cjson.dll | `75cde82d74d0d2f350bd0fee30bbf5971787d11f5b657a9381ab946132a11051` |
| json.lua | `0eaccda57fabc0330736de25f45cf589821a42b5e0fe02e4e3125f7dc0bf2b7e` |
| luasocket/core.dll | `b0ad8ab91f4ba40ca0cbb6fe11207a91b4b853f44b7515e1ec5c1c5f52269b9f` |
| luasocket/socket.lua | `a92ae132ce092dc5b8e164ccbc7c737f987b8bbbd481b531db9b64d6c2be4e11` |

BUILD.md is excluded from its own hash table. Static validation and in-game acceptance are separate; a successful compile alone does not establish compatibility in X4.

## Post-build Defender scan for this handoff

- Finished UTC: 2026-10-26T11:16:14.934603+00:00
- File: aickeys/aickeys.dll SHA256 `449931735c7d2c719d085b03a4e90a0cf9b88d5da6aa457ae20f4ac29d68caf7`
- Scanner: Microsoft Defender 4.18.26090.9-0; signatures 1.461.208.0
- Command: `MpCmdRun.exe -Scan -ScanType 3 -File <staged aickeys.dll> -DisableRemediation`
- Exit code: 0. Output explicitly reported "found no threats"; file hash unchanged.
- Scope: this file and these signatures only; not game validation or a guarantee of all future scanners. Re-scan the release-candidate bytes before each release candidate, as SPEC-854 requires.
- Full receipt: C:/aicb/854-20261026/evidence/defender-scan.json
