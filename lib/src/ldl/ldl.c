#include "ldl.h"

#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <assert.h>

#define LDL_ITERATOR_TABLE "LDL_ITERATOR_TABLE"

ldl_ctx_t ldl_ctx_create()
{
    ldl_ctx_t ctx;
    ctx.lua_state = luaL_newstate();
    if (!ctx.lua_state)
        return ctx;
    luaL_openlibs(ctx.lua_state);
    lua_createtable(ctx.lua_state , 0, 0); // Create the iterator thread table
    lua_setfield(ctx.lua_state , LUA_GLOBALSINDEX, LDL_ITERATOR_TABLE);  // Register it
    return ctx;
}

int32_t ldl_ctx_destroy(ldl_ctx_t * ctx)
{
    if (!ctx)
        return -1;
    lua_close(ctx->lua_state);
    ctx->lua_state = 0;
    return 0;
}

int32_t ldl_ctx_is_valid(const ldl_ctx_t * ctx)
{
    if (!ctx)
        return 0;
    return (int32_t) (int64_t) ctx->lua_state;
}

int32_t ldl_ctx_execute(ldl_ctx_t * ctx, const char * code)
{
    if (!ctx)
        return -1;
    if (luaL_loadstring(ctx->lua_state, code) || lua_pcall(ctx->lua_state, 0, LUA_MULTRET, 0))
    {
        perror(lua_tostring(ctx->lua_state, -1));
        return -1;
    }
    return 0;
}

int32_t ldl_ctx_execute_file(ldl_ctx_t * ctx, const char * file_path)
{
    if (!ctx)
        return -1;
    if (luaL_loadfile(ctx->lua_state, file_path) || lua_pcall(ctx->lua_state, 0, LUA_MULTRET, 0))
    {
        perror(lua_tostring(ctx->lua_state, -1));
        return -1;
    }
    return 0;
}

struct ldl_node_t ldl_ctx_resolve_node(ldl_ctx_t * ctx, const char * node_path)
{
    lua_State * ls = ctx->lua_state; // Current lua context
    lua_State * lt; // New thread on context
    ldl_node_t node; // Node referenced by node_path
    if (!ctx)
        return node;

    //Get the iterator thread table
    lua_getfield(ls, LUA_GLOBALSINDEX, LDL_ITERATOR_TABLE);
    assert(lua_istable(ls, 1) && "LDL ASSERT : _G[LDL_ITERATOR_TABLE] IS NOT A TABLE");

    // Prepare the key for the iterator thread
    lua_pushnumber(ls, lua_objlen(ls, 1)+1);

    // Create a new thread to explore context independently
    lt = lua_newthread(ls);
    if (!lt)
    {
        perror("Fatal : Impossible to create new thread");
        node.ctx = ctx;
        node.lua_state = 0;
        return node;
    }

    // Register the thread in the global table
    lua_settable(ls, 1);
    lua_setfield(ls, LUA_GLOBALSINDEX, LDL_ITERATOR_TABLE);
}