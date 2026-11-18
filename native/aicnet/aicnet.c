/* AiLive HTTPS transport (aicnet). First-party; compiled into lua3p/luasocket/core.dll beside LuaSocket.
 *
 * Requests run on a worker thread through Windows' own WinHTTP: the system's TLS (1.2 or newer) and certificate
 * store, certificate errors are never ignored, nothing to bundle or keep updated. Lua starts a request and polls it.
 *
 * API keys: stored with Windows DPAPI for the current Windows user, in %LOCALAPPDATA%\AiLive\keys\<name>.dat -
 * never in the X4 save, never in a log. Each key is bound to one host (inside the encryption, so editing the file
 * breaks it). Lua can store, describe (host + last four characters) and clear a key, but never read it back: the DLL
 * itself adds "Authorization: Bearer ..." to an HTTPS request for exactly that host, with redirects refused.
 */
#include <windows.h>
#include <winhttp.h>
#include <wincrypt.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"

#define AICNET_SLOTS 16
#define AICNET_MAX_BODY (16u * 1024u * 1024u)
#define AICNET_MAX_SEND (4u * 1024u * 1024u)
#define AICNET_MAX_URL 2048
#define AICNET_MAX_HDR 8192
#define AICNET_ERR 200

#ifndef WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3
#define WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3 0x00002000
#endif

typedef struct {
    LONG state;          /* 0 free, 1 running, 2 done, 3 running but abandoned (result discarded) */
    unsigned gen;
    int status;
    char *body;
    size_t len;
    char err[AICNET_ERR];
} Slot;

typedef struct {
    int slot;
    unsigned gen;
    wchar_t *url;
    wchar_t *method;
    wchar_t *headers;    /* "Name: value\r\n" lines, validated */
    char *body;
    DWORD blen;
    DWORD timeout;
    char *secret;        /* plaintext key for this one request; zeroed and freed by the worker */
    wchar_t keyhost[256];
} Job;

static Slot g_slots[AICNET_SLOTS];
static CRITICAL_SECTION g_cs;
static INIT_ONCE g_once = INIT_ONCE_STATIC_INIT;
static unsigned g_gen = 0;

static BOOL CALLBACK aicnet_init(PINIT_ONCE once, PVOID param, PVOID *ctx)
{
    (void)once; (void)param; (void)ctx;
    InitializeCriticalSection(&g_cs);
    return TRUE;
}

static void wipe_free(char *p, size_t n)
{
    if (p) { SecureZeroMemory(p, n); free(p); }
}

static wchar_t *to_wide(const char *s, size_t n)
{
    int w;
    wchar_t *out;
    if (n > 0x7fffffff) return NULL;
    w = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, (int)n, NULL, 0);
    if (w < 0 || (n > 0 && w == 0)) return NULL;
    out = (wchar_t *)calloc((size_t)w + 1, sizeof(wchar_t));
    if (!out) return NULL;
    if (n > 0 && MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, (int)n, out, w) != w) { free(out); return NULL; }
    return out;
}

/* ---------------------------------------------------------------- key store (DPAPI, current user) */
static int valid_name(const char *s)
{
    size_t i, n = strlen(s);
    if (n < 1 || n > 32) return 0;
    for (i = 0; i < n; ++i)
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_')) return 0;
    return 1;
}

static int valid_host(const char *s)
{
    size_t i, n = strlen(s);
    if (n < 3 || n > 253) return 0;
    for (i = 0; i < n; ++i)
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '.' || s[i] == '-')) return 0;
    return 1;
}

static int key_path(const char *name, wchar_t *out, size_t cap, int create)
{
    wchar_t base[MAX_PATH], wname[40];
    DWORD n = GetEnvironmentVariableW(L"LOCALAPPDATA", base, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) return 0;
    if (MultiByteToWideChar(CP_UTF8, 0, name, -1, wname, 40) == 0) return 0;
    if (create) {
        wchar_t dir[MAX_PATH + 32];
        if (_snwprintf_s(dir, MAX_PATH + 32, _TRUNCATE, L"%s\\AiLive", base) < 0) return 0;
        CreateDirectoryW(dir, NULL);
        if (_snwprintf_s(dir, MAX_PATH + 32, _TRUNCATE, L"%s\\AiLive\\keys", base) < 0) return 0;
        CreateDirectoryW(dir, NULL);
    }
    return _snwprintf_s(out, cap, _TRUNCATE, L"%s\\AiLive\\keys\\%s.dat", base, wname) > 0;
}

static void entropy_for(const char *name, const char *host, char *buf, size_t cap)
{
    _snprintf_s(buf, cap, _TRUNCATE, "AiLive|%s|%s", name, host);
}

/* file: "AIK1" + host length (1 byte) + host + DPAPI blob */
static int key_store(const char *name, const char *host, const char *secret, size_t slen, char *err)
{
    wchar_t path[MAX_PATH + 64], tmp[MAX_PATH + 72];
    char ent[300];
    DATA_BLOB in, out, eb;
    HANDLE f;
    DWORD wrote;
    unsigned char hdr[5 + 253];
    size_t hlen = strlen(host);
    int ok = 0;
    if (!key_path(name, path, MAX_PATH + 64, 1)) { strcpy_s(err, AICNET_ERR, "no profile folder"); return 0; }
    entropy_for(name, host, ent, sizeof ent);
    in.pbData = (BYTE *)secret; in.cbData = (DWORD)slen;
    eb.pbData = (BYTE *)ent; eb.cbData = (DWORD)strlen(ent);
    if (!CryptProtectData(&in, L"AiLive API key", &eb, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &out)) {
        strcpy_s(err, AICNET_ERR, "Windows could not protect the key"); return 0;
    }
    memcpy(hdr, "AIK1", 4); hdr[4] = (unsigned char)hlen; memcpy(hdr + 5, host, hlen);
    _snwprintf_s(tmp, MAX_PATH + 72, _TRUNCATE, L"%s.tmp", path);
    f = CreateFileW(tmp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f != INVALID_HANDLE_VALUE) {
        ok = WriteFile(f, hdr, (DWORD)(5 + hlen), &wrote, NULL) && wrote == 5 + hlen
            && WriteFile(f, out.pbData, out.cbData, &wrote, NULL) && wrote == out.cbData;
        CloseHandle(f);
        ok = ok && MoveFileExW(tmp, path, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
        if (!ok) DeleteFileW(tmp);
    }
    SecureZeroMemory(out.pbData, out.cbData);
    LocalFree(out.pbData);
    if (!ok) strcpy_s(err, AICNET_ERR, "the key file could not be written");
    return ok;
}

/* returns a malloc'd plaintext secret (caller wipes and frees) and the bound host */
static char *key_load(const char *name, char *host, size_t hcap, size_t *slen, char *err)
{
    wchar_t path[MAX_PATH + 64];
    HANDLE f;
    LARGE_INTEGER size;
    unsigned char *raw = NULL;
    DWORD got = 0;
    DATA_BLOB in, out, eb;
    char ent[300];
    char *secret = NULL;
    size_t hlen;
    if (!valid_name(name) || !key_path(name, path, MAX_PATH + 64, 0)) { strcpy_s(err, AICNET_ERR, "no saved key"); return NULL; }
    f = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f == INVALID_HANDLE_VALUE) { strcpy_s(err, AICNET_ERR, "no saved key"); return NULL; }
    if (!GetFileSizeEx(f, &size) || size.QuadPart < 8 || size.QuadPart > 65536) { CloseHandle(f); strcpy_s(err, AICNET_ERR, "the saved key is damaged"); return NULL; }
    raw = (unsigned char *)malloc((size_t)size.QuadPart);
    if (raw && !(ReadFile(f, raw, (DWORD)size.QuadPart, &got, NULL) && got == (DWORD)size.QuadPart)) { free(raw); raw = NULL; }
    CloseHandle(f);
    if (!raw) { strcpy_s(err, AICNET_ERR, "the saved key could not be read"); return NULL; }
    hlen = raw[4];
    if (memcmp(raw, "AIK1", 4) != 0 || hlen < 3 || hlen + 1 > hcap || 5 + hlen >= got) {
        free(raw); strcpy_s(err, AICNET_ERR, "the saved key is damaged"); return NULL;
    }
    memcpy(host, raw + 5, hlen); host[hlen] = 0;
    entropy_for(name, host, ent, sizeof ent);
    in.pbData = raw + 5 + hlen; in.cbData = got - (DWORD)(5 + hlen);
    eb.pbData = (BYTE *)ent; eb.cbData = (DWORD)strlen(ent);
    if (CryptUnprotectData(&in, NULL, &eb, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &out)) {
        secret = (char *)malloc((size_t)out.cbData + 1);
        if (secret) { memcpy(secret, out.pbData, out.cbData); secret[out.cbData] = 0; *slen = out.cbData; }
        SecureZeroMemory(out.pbData, out.cbData);
        LocalFree(out.pbData);
    }
    free(raw);
    if (!secret) strcpy_s(err, AICNET_ERR, "the saved key belongs to another Windows user or was changed");
    return secret;
}

/* ---------------------------------------------------------------- the worker */
static void publish(Job *j, int status, char *buf, size_t len, const char *err)
{
    Slot *s = &g_slots[j->slot];
    EnterCriticalSection(&g_cs);
    if (s->gen == j->gen && s->state == 1) {
        s->status = status; s->body = buf; s->len = len;
        strcpy_s(s->err, AICNET_ERR, err ? err : "");
        s->state = 2;
        buf = NULL;
    } else if (s->gen == j->gen && s->state == 3) {
        s->state = 0;
    }
    LeaveCriticalSection(&g_cs);
    free(buf);
}

static int abandoned(Job *j)
{
    LONG st;
    EnterCriticalSection(&g_cs);
    st = (g_slots[j->slot].gen == j->gen) ? g_slots[j->slot].state : 3;
    LeaveCriticalSection(&g_cs);
    return st == 3;
}

static unsigned __stdcall worker(void *p)
{
    Job *j = (Job *)p;
    HINTERNET s = NULL, c = NULL, r = NULL;
    URL_COMPONENTS u;
    wchar_t host[256], path[AICNET_MAX_URL], extra[AICNET_MAX_URL], full[AICNET_MAX_URL * 2];
    char *buf = NULL;
    size_t len = 0, cap = 0;
    int status = 0;
    const char *err = NULL;
    DWORD prot, code = 0, sz = sizeof(code), avail = 0, got = 0, t = j->timeout;

    ZeroMemory(&u, sizeof(u));
    u.dwStructSize = sizeof(u);
    u.lpszHostName = host; u.dwHostNameLength = 256;
    u.lpszUrlPath = path; u.dwUrlPathLength = AICNET_MAX_URL;
    u.lpszExtraInfo = extra; u.dwExtraInfoLength = AICNET_MAX_URL;
    if (!WinHttpCrackUrl(j->url, 0, 0, &u)) { err = "the address could not be read"; goto done; }
    if (u.nScheme != INTERNET_SCHEME_HTTPS) { err = "only https addresses are allowed"; goto done; }
    if (j->secret && _wcsicmp(host, j->keyhost) != 0) { err = "the saved key belongs to another address"; goto done; }
    _snwprintf_s(full, AICNET_MAX_URL * 2, _TRUNCATE, L"%s%s", path, extra);

    s = WinHttpOpen(L"AiLive/1", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!s) s = WinHttpOpen(L"AiLive/1", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!s) { err = "Windows networking is unavailable"; goto done; }
    prot = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3;
    if (!WinHttpSetOption(s, WINHTTP_OPTION_SECURE_PROTOCOLS, &prot, sizeof(prot))) {
        prot = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
        if (!WinHttpSetOption(s, WINHTTP_OPTION_SECURE_PROTOCOLS, &prot, sizeof(prot))) { err = "TLS 1.2 is unavailable"; goto done; }
    }
    WinHttpSetTimeouts(s, (int)t, (int)t, (int)t, (int)t);
    c = WinHttpConnect(s, host, u.nPort, 0);
    if (!c) { err = "could not reach the server"; goto done; }
    r = WinHttpOpenRequest(c, j->method, full, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!r) { err = "could not open the request"; goto done; }
    if (j->secret) {
        DWORD never = WINHTTP_OPTION_REDIRECT_POLICY_NEVER;
        wchar_t auth[700];
        int n;
        WinHttpSetOption(r, WINHTTP_OPTION_REDIRECT_POLICY, &never, sizeof(never));
        n = _snwprintf_s(auth, 700, _TRUNCATE, L"Authorization: Bearer %S\r\n", j->secret);
        if (n <= 0 || !WinHttpAddRequestHeaders(r, auth, (DWORD)-1L, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE)) {
            SecureZeroMemory(auth, sizeof(auth)); err = "could not attach the key"; goto done;
        }
        SecureZeroMemory(auth, sizeof(auth));
    }
    wipe_free(j->secret, j->secret ? strlen(j->secret) : 0); j->secret = NULL;
    if (j->headers && j->headers[0] && !WinHttpAddRequestHeaders(r, j->headers, (DWORD)-1L, WINHTTP_ADDREQ_FLAG_ADD)) {
        err = "a request header was refused"; goto done;
    }
    if (!WinHttpSendRequest(r, WINHTTP_NO_ADDITIONAL_HEADERS, 0, j->blen ? j->body : WINHTTP_NO_REQUEST_DATA, j->blen, j->blen, 0)) {
        DWORD e = GetLastError();
        err = (e == ERROR_WINHTTP_TIMEOUT) ? "timed out" : (e == ERROR_WINHTTP_SECURE_FAILURE) ? "the server's certificate was not trusted"
            : (e == ERROR_WINHTTP_NAME_NOT_RESOLVED) ? "the server name was not found" : "could not send the request";
        goto done;
    }
    if (!WinHttpReceiveResponse(r, NULL)) { err = (GetLastError() == ERROR_WINHTTP_TIMEOUT) ? "timed out" : "no response"; goto done; }
    if (WinHttpQueryHeaders(r, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &code, &sz, WINHTTP_NO_HEADER_INDEX))
        status = (int)code;
    for (;;) {
        if (abandoned(j)) { err = "cancelled"; break; }
        if (!WinHttpQueryDataAvailable(r, &avail)) { err = "the response was cut off"; break; }
        if (avail == 0) break;
        if (len + avail > AICNET_MAX_BODY) { err = "the response is too large"; break; }
        if (len + avail + 1 > cap) {
            size_t ncap = cap ? cap * 2 : 65536;
            char *nb;
            while (ncap < len + avail + 1) ncap *= 2;
            nb = (char *)realloc(buf, ncap);
            if (!nb) { err = "out of memory"; break; }
            buf = nb; cap = ncap;
        }
        if (!WinHttpReadData(r, buf + len, avail, &got)) { err = "the response was cut off"; break; }
        len += got;
    }
done:
    if (r) WinHttpCloseHandle(r);
    if (c) WinHttpCloseHandle(c);
    if (s) WinHttpCloseHandle(s);
    wipe_free(j->secret, j->secret ? strlen(j->secret) : 0);
    publish(j, status, buf, len, err);
    free(j->url); free(j->method); free(j->headers); free(j->body); free(j);
    return 0;
}

/* ---------------------------------------------------------------- Lua API */
static int bad_text(const char *s, size_t n)
{
    size_t i;
    for (i = 0; i < n; ++i) if (s[i] == '\r' || s[i] == '\n' || s[i] == 0) return 1;
    return 0;
}

/* request(method, url, headers_table|nil, body|nil, timeout_ms|nil, keyname|nil) -> id | nil, err */
static int l_request(lua_State *L)
{
    const char *method = luaL_checkstring(L, 1);
    size_t ulen, blen = 0, hl = 0;
    const char *url = luaL_checklstring(L, 2, &ulen);
    const char *body = lua_isnoneornil(L, 4) ? NULL : luaL_checklstring(L, 4, &blen);
    lua_Number tms = luaL_optnumber(L, 5, 60000);
    const char *keyname = luaL_optstring(L, 6, NULL);
    char hdr[AICNET_MAX_HDR], err[AICNET_ERR], khost[256];
    Job *j;
    int i, slot = -1;
    uintptr_t th;
    lua_Number id;
    InitOnceExecuteOnce(&g_once, aicnet_init, NULL, NULL);
    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0) { lua_pushnil(L); lua_pushliteral(L, "only GET and POST"); return 2; }
    if (ulen < 9 || ulen > AICNET_MAX_URL || _strnicmp(url, "https://", 8) != 0 || bad_text(url, ulen)) {
        lua_pushnil(L); lua_pushliteral(L, "only https addresses are allowed"); return 2;
    }
    if (blen > AICNET_MAX_SEND) { lua_pushnil(L); lua_pushliteral(L, "the request body is too large"); return 2; }
    hdr[0] = 0;
    if (lua_istable(L, 3)) {
        lua_pushnil(L);
        while (lua_next(L, 3) != 0) {
            size_t kn, vn;
            const char *k, *v;
            /* pop only the value: lua_next needs the key on the stack to continue */
            if (lua_type(L, -2) != LUA_TSTRING || lua_type(L, -1) != LUA_TSTRING) { lua_pop(L, 1); continue; }
            k = lua_tolstring(L, -2, &kn); v = lua_tolstring(L, -1, &vn);
            if (kn == 0 || bad_text(k, kn) || bad_text(v, vn) || strchr(k, ':') || _stricmp(k, "host") == 0
                    || (keyname && _stricmp(k, "authorization") == 0)) { lua_pop(L, 1); continue; }
            if (hl + kn + vn + 4 >= sizeof(hdr)) { lua_pop(L, 3); lua_pushnil(L); lua_pushliteral(L, "too many headers"); return 2; }
            memcpy(hdr + hl, k, kn); hl += kn; hdr[hl++] = ':'; hdr[hl++] = ' ';
            memcpy(hdr + hl, v, vn); hl += vn; hdr[hl++] = '\r'; hdr[hl++] = '\n'; hdr[hl] = 0;
            lua_pop(L, 1);
        }
    }
    j = (Job *)calloc(1, sizeof(Job));
    if (!j) { lua_pushnil(L); lua_pushliteral(L, "out of memory"); return 2; }
    if (keyname) {
        size_t slen = 0;
        j->secret = key_load(keyname, khost, sizeof(khost), &slen, err);
        if (!j->secret) { free(j); lua_pushnil(L); lua_pushstring(L, err); return 2; }
        MultiByteToWideChar(CP_UTF8, 0, khost, -1, j->keyhost, 256);
    }
    j->url = to_wide(url, ulen);
    j->method = to_wide(method, strlen(method));
    j->headers = to_wide(hdr, hl);
    if (blen) { j->body = (char *)malloc(blen); if (j->body) memcpy(j->body, body, blen); }
    j->blen = (DWORD)blen;
    j->timeout = (DWORD)((tms >= 1000 && tms <= 600000) ? tms : 60000);
    if (!j->url || !j->method || !j->headers || (blen && !j->body)) {
        wipe_free(j->secret, j->secret ? strlen(j->secret) : 0);
        free(j->url); free(j->method); free(j->headers); free(j->body); free(j);
        lua_pushnil(L); lua_pushliteral(L, "the request could not be prepared"); return 2;
    }
    EnterCriticalSection(&g_cs);
    for (i = 0; i < AICNET_SLOTS; ++i) if (g_slots[i].state == 0) { slot = i; break; }
    if (slot >= 0) {
        g_slots[slot].state = 1; g_slots[slot].gen = ++g_gen; g_slots[slot].status = 0;
        g_slots[slot].body = NULL; g_slots[slot].len = 0; g_slots[slot].err[0] = 0;
        j->slot = slot; j->gen = g_slots[slot].gen;
    }
    LeaveCriticalSection(&g_cs);
    if (slot < 0) {
        wipe_free(j->secret, j->secret ? strlen(j->secret) : 0);
        free(j->url); free(j->method); free(j->headers); free(j->body); free(j);
        lua_pushnil(L); lua_pushliteral(L, "too many requests in flight"); return 2;
    }
    /* the worker owns and frees j once it starts: take the id first and never touch j afterwards (726, review P1) */
    id = (lua_Number)j->gen * AICNET_SLOTS + slot;
    th = _beginthreadex(NULL, 0, worker, j, 0, NULL);
    if (th == 0) {
        EnterCriticalSection(&g_cs); g_slots[slot].state = 0; LeaveCriticalSection(&g_cs);
        wipe_free(j->secret, j->secret ? strlen(j->secret) : 0);
        free(j->url); free(j->method); free(j->headers); free(j->body); free(j);
        lua_pushnil(L); lua_pushliteral(L, "could not start the request"); return 2;
    }
    CloseHandle((HANDLE)th);
    lua_pushnumber(L, id);
    return 1;
}

static int decode_id(lua_State *L, int *slot, unsigned *gen)
{
    lua_Number n = luaL_checknumber(L, 1);
    if (!(n >= 0 && n < 4294967296.0 * AICNET_SLOTS)) return 0;
    *slot = (int)((unsigned long long)n % AICNET_SLOTS);
    *gen = (unsigned)((unsigned long long)n / AICNET_SLOTS);
    return 1;
}

/* poll(id) -> nil while running | status, body, err|nil when finished */
static int l_poll(lua_State *L)
{
    int slot;
    unsigned gen;
    Slot *s;
    char *body = NULL;
    size_t len = 0;
    int status = 0, ready = 0;
    char err[AICNET_ERR];
    err[0] = 0;
    InitOnceExecuteOnce(&g_once, aicnet_init, NULL, NULL);
    if (!decode_id(L, &slot, &gen)) { lua_pushinteger(L, 0); lua_pushliteral(L, ""); lua_pushliteral(L, "unknown request"); return 3; }
    s = &g_slots[slot];
    EnterCriticalSection(&g_cs);
    if (s->gen != gen || s->state == 0 || s->state == 3) { strcpy_s(err, AICNET_ERR, "unknown request"); ready = 1; }
    else if (s->state == 2) {
        status = s->status; body = s->body; len = s->len; strcpy_s(err, AICNET_ERR, s->err);
        s->body = NULL; s->len = 0; s->state = 0; ready = 1;
    }
    LeaveCriticalSection(&g_cs);
    if (!ready) { lua_pushnil(L); return 1; }
    lua_pushinteger(L, status);
    lua_pushlstring(L, body ? body : "", len);
    free(body);
    if (err[0]) lua_pushstring(L, err); else lua_pushnil(L);
    return 3;
}

static int l_cancel(lua_State *L)
{
    int slot;
    unsigned gen;
    InitOnceExecuteOnce(&g_once, aicnet_init, NULL, NULL);
    if (decode_id(L, &slot, &gen)) {
        EnterCriticalSection(&g_cs);
        if (g_slots[slot].gen == gen) {
            if (g_slots[slot].state == 1) g_slots[slot].state = 3;
            else if (g_slots[slot].state == 2) { free(g_slots[slot].body); g_slots[slot].body = NULL; g_slots[slot].state = 0; }
        }
        LeaveCriticalSection(&g_cs);
    }
    return 0;
}

/* keyset(name, host, secret) -> true | nil, err */
static int l_keyset(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    const char *host = luaL_checkstring(L, 2);
    size_t slen, i;
    const char *secret = luaL_checklstring(L, 3, &slen);
    char err[AICNET_ERR];
    if (!valid_name(name)) { lua_pushnil(L); lua_pushliteral(L, "bad key name"); return 2; }
    if (!valid_host(host)) { lua_pushnil(L); lua_pushliteral(L, "bad host"); return 2; }
    if (slen < 8 || slen > 512) { lua_pushnil(L); lua_pushliteral(L, "that does not look like an API key"); return 2; }
    for (i = 0; i < slen; ++i)
        if (secret[i] < 0x21 || secret[i] > 0x7e) { lua_pushnil(L); lua_pushliteral(L, "that does not look like an API key"); return 2; }
    if (!key_store(name, host, secret, slen, err)) { lua_pushnil(L); lua_pushstring(L, err); return 2; }
    lua_pushboolean(L, 1);
    return 1;
}

/* keyclip(name, host, prefix) -> hint | nil, err
 * The key goes from the Windows clipboard straight into DPAPI: never typed, never on screen, never in Lua.
 * On success the clipboard is emptied so the key does not linger there. */
static int l_keyclip(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    const char *host = luaL_checkstring(L, 2);
    const char *prefix = luaL_optstring(L, 3, "");
    char key[520], err[AICNET_ERR], hint[8];
    size_t n = 0, i, a = 0;
    HANDLE h;
    const wchar_t *w;
    int stored = 0;
    key[0] = 0;
    if (!valid_name(name) || !valid_host(host)) { lua_pushnil(L); lua_pushliteral(L, "bad key name or host"); return 2; }
    if (!OpenClipboard(NULL)) { lua_pushnil(L); lua_pushliteral(L, "the clipboard is busy - try again"); return 2; }
    h = GetClipboardData(CF_UNICODETEXT);
    if (h && (w = (const wchar_t *)GlobalLock(h)) != NULL) {
        if (WideCharToMultiByte(CP_UTF8, 0, w, -1, key, (int)sizeof(key), NULL, NULL) <= 0) key[0] = 0;
        GlobalUnlock(h);
    }
    n = strlen(key);
    while (n > 0 && (key[n - 1] == ' ' || key[n - 1] == '\r' || key[n - 1] == '\n' || key[n - 1] == '\t')) key[--n] = 0;
    while (a < n && (key[a] == ' ' || key[a] == '\r' || key[a] == '\n' || key[a] == '\t')) ++a;
    if (a) { memmove(key, key + a, n - a + 1); n -= a; }
    for (i = 0; i < n; ++i) if (key[i] < 0x21 || key[i] > 0x7e) break;
    if (n < 8 || n > 512 || i < n || (prefix[0] && strncmp(key, prefix, strlen(prefix)) != 0)) {
        CloseClipboard();
        SecureZeroMemory(key, sizeof(key));
        lua_pushnil(L);
        lua_pushstring(L, prefix[0] ? "the clipboard does not hold a key that starts with the expected letters"
                                    : "the clipboard does not hold an API key");
        return 2;
    }
    stored = key_store(name, host, key, n, err);
    if (stored) EmptyClipboard();
    CloseClipboard();
    _snprintf_s(hint, sizeof(hint), _TRUNCATE, "...%s", key + n - 4);
    SecureZeroMemory(key, sizeof(key));
    if (!stored) { lua_pushnil(L); lua_pushstring(L, err); return 2; }
    lua_pushstring(L, hint);
    return 1;
}

/* keyinfo(name) -> host, hint ("...abcd") | nil, err */
static int l_keyinfo(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    char host[256], err[AICNET_ERR], hint[8];
    size_t slen = 0;
    char *secret = key_load(name, host, sizeof(host), &slen, err);
    if (!secret) { lua_pushnil(L); lua_pushstring(L, err); return 2; }
    _snprintf_s(hint, sizeof(hint), _TRUNCATE, "...%s", slen > 4 ? secret + slen - 4 : "");
    wipe_free(secret, slen);
    lua_pushstring(L, host);
    lua_pushstring(L, hint);
    return 2;
}

/* keyclear(name) -> true once no saved key remains | nil, reason (726, review P2: a failed delete is not "forgotten") */
static int l_keyclear(lua_State *L)
{
    const char *name = luaL_checkstring(L, 1);
    wchar_t path[MAX_PATH + 64];
    if (!valid_name(name) || !key_path(name, path, MAX_PATH + 64, 0)) {
        lua_pushnil(L); lua_pushliteral(L, "bad key name"); return 2;
    }
    if (!DeleteFileW(path)) {
        DWORD e = GetLastError();
        if (e != ERROR_FILE_NOT_FOUND && e != ERROR_PATH_NOT_FOUND) {
            lua_pushnil(L); lua_pushliteral(L, "the saved key could not be removed"); return 2;
        }
    }
    if (GetFileAttributesW(path) != INVALID_FILE_ATTRIBUTES) {
        lua_pushnil(L); lua_pushliteral(L, "the saved key could not be removed"); return 2;
    }
    lua_pushboolean(L, 1);
    return 1;
}

__declspec(dllexport) int luaopen_aicnet(lua_State *L)
{
    const luaL_Reg fns[] = {{"request", l_request}, {"poll", l_poll}, {"cancel", l_cancel},
        {"keyset", l_keyset}, {"keyclip", l_keyclip}, {"keyinfo", l_keyinfo}, {"keyclear", l_keyclear}, {NULL, NULL}};
    HMODULE self = NULL;
    int i;
    InitOnceExecuteOnce(&g_once, aicnet_init, NULL, NULL);
    /* Worker threads may outlive a closed Lua state (a UI reload): keep this DLL loaded until X4 exits. */
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN, (LPCWSTR)(void *)luaopen_aicnet, &self);
    /* A new Lua state (UI reload) cannot poll the old state's requests: discard them as they finish. */
    EnterCriticalSection(&g_cs);
    for (i = 0; i < AICNET_SLOTS; ++i) {
        if (g_slots[i].state == 2) { free(g_slots[i].body); g_slots[i].body = NULL; g_slots[i].state = 0; }
        else if (g_slots[i].state == 1) g_slots[i].state = 3;
    }
    LeaveCriticalSection(&g_cs);
    lua_newtable(L);
    luaL_register(L, NULL, fns);
    lua_pushliteral(L, "aicnet 1");
    lua_setfield(L, -2, "version");
    return 1;
}
