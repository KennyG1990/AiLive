/* AiLive foreground-only key polling. No retained state or event hooks. */
#include <windows.h>
#include "lua.h"
#include "lauxlib.h"

int aickeys_is_foreground(void)
{
    DWORD pid = 0;
    HWND window = GetForegroundWindow();
    return window != NULL && GetWindowThreadProcessId(window, &pid) != 0
        && pid == GetCurrentProcessId();
}

int aickeys_foreground(lua_State *L)
{
    lua_pushboolean(L, aickeys_is_foreground());
    return 1;
}

int aickeys_poll(lua_State *L)
{
    int i, vk;
    int count = lua_gettop(L);
    lua_Number number;
    if (count < 1 || count > 64)
        return luaL_error(L, "poll requires 1 to 64 virtual-key integers");
    for (i = 1; i <= count; ++i) {
        number = lua_tonumber(L, i);
        if (lua_type(L, i) != LUA_TNUMBER || !(number >= 0 && number <= 0x7b)
                || number != (lua_Number)(int)number)
            return luaL_argerror(L, i, "expected an allowlisted virtual-key integer");
        vk = (int)number;
        if (!((vk >= 0x10 && vk <= 0x12) || (vk >= 0x30 && vk <= 0x39)
                || (vk >= 0x41 && vk <= 0x5a) || (vk >= 0x60 && vk <= 0x6f)
                || (vk >= 0x70 && vk <= 0x7b)))
            return luaL_argerror(L, i, "virtual key is not allowlisted");
    }
    if (!aickeys_is_foreground()) {
        lua_pushnil(L);
        return 1;
    }
    luaL_checkstack(L, count, "poll result stack");
    for (i = 1; i <= count; ++i)
        lua_pushboolean(L, (GetAsyncKeyState((int)lua_tointeger(L, i)) & 0x8000) != 0);
    return count;
}

__declspec(dllexport) int luaopen_aickeys(lua_State *L)
{
    const luaL_Reg fns[] = {{"poll", aickeys_poll}, {"foreground", aickeys_foreground}, {NULL, NULL}};
    lua_createtable(L, 0, 4);
    luaL_register(L, NULL, fns);
    lua_pushliteral(L, "aickeys 1");
    lua_setfield(L, -2, "_VERSION");
    lua_pushinteger(L, 64);
    lua_setfield(L, -2, "MAX");
    return 1;
}
