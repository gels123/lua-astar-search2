/*
 *  author: gels
 *  date: 2021-12-28 20:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "wrapper.h"
#include "lua-mapSearch.h"

static inline void* _toMapSearch(lua_State *L) {
    void **ppms = (void**) lua_touserdata(L, 1);
    if(ppms == NULL) {
        luaL_error(L, "lua-mapSearch.c::_toMapSearch error: must be MapSearch obj");
        return NULL;
    }
    return *ppms;
}

static int l_create(lua_State *L) 
{
    void *pms = create();
    if(pms == NULL) {
        return 0;
    }
    void **ppms = (void**) lua_newuserdata(L, sizeof(void*));
    *ppms = pms;
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_setmetatable(L, -2);
    return 1;
}

static int l_release(lua_State *L)
{
    void *pms = _toMapSearch(L);
    printf("lua-mapSearch.c::l_release pms:%p\n", pms);
    release(pms);
    return 0;
}

int l_testFun(lua_State *L)
{   
    void *pms = _toMapSearch(L);
	int a = luaL_checknumber(L, 2);
    int b = luaL_checknumber(L, 3);
    printf("lua-mapSearch.c::l_testFun enter a=%d, b=%d\n", a, b);
    int num = testFun(pms, a, b);
    lua_pushinteger(L, num);
	return 1;
}

// init map, 0 for fail and 1 for success
int l_init(lua_State *L)
{   
    void *pms = _toMapSearch(L);
	unsigned int mapType = luaL_checknumber(L, 2);
    unsigned int mapSize = luaL_checknumber(L, 3);
    size_t len;
    const char* mapFile = lua_tolstring(L, 4, &len);
    printf("lua-mapSearch.c::l_init enter mapType=%d, mapSize=%d mapFile=%s\n", mapType, mapSize, mapFile);
    
    int num = init(pms, mapType, mapSize, mapFile);
    lua_pushboolean(L, num);
	return 1;
}

int l_findPath(lua_State *L)
{
    void *pms = _toMapSearch(L);
    unsigned int x1 = luaL_checknumber(L, 2);
    unsigned int y1 = luaL_checknumber(L, 3);
    unsigned int x2 = luaL_checknumber(L, 4);
    unsigned int y2 = luaL_checknumber(L, 5);

    Path* ptr = findPath(pms, x1, y1, x2, y2);
    if(ptr == NULL || ptr->ps == NULL) {
		lua_pushnil(L);
		return 1;
	}
    printf("==findPath end count=%d\n", ptr->count);
    lua_createtable(L, ptr->count*2, 0);
    int n = 0;
    Pos* tmp = ptr->ps;
    for(int i=0; i<ptr->count; i++) {
        lua_pushinteger(L, tmp->x);
        ++n;
        lua_rawseti(L, -2, n);
        ++n;
        lua_pushinteger(L, tmp->y);
        lua_rawseti(L, -2, n);
        ++tmp;
    }
    releasePath(ptr);
    return 1;
}

LUALIB_API int luaopen_mapSearch(lua_State *L)
{
    luaL_checkversion(L);

    luaL_Reg l[] = {
        {"testFun", l_testFun},
        {"init", l_init},
        {"findPath", l_findPath},
        {NULL, NULL},
    };

    lua_createtable(L, 0, 2);

    luaL_newlib(L, l);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, l_release);
    lua_setfield(L, -2, "__gc");

    lua_pushcclosure(L, l_create, 1);

    return 1;
}

