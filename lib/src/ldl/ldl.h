#ifndef __LDL_H__
#define __LDL_H__

#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lua_State lua_State;

typedef struct ldl_ctx_t
{
    lua_State * lua_state;
} ldl_ctx_t;

typedef struct ldl_node_t
{
    ldl_ctx_t  * ctx;
    lua_State  * lua_state;
} ldl_node_t;

ldl_ctx_t ldl_ctx_create();
int32_t ldl_ctx_destroy(ldl_ctx_t * ctx);
int32_t ldl_ctx_is_valid(const ldl_ctx_t * ctx);
int32_t ldl_ctx_execute(ldl_ctx_t * ctx, const char * code);
int32_t ldl_ctx_execute_file(ldl_ctx_t * ctx, const char * file_path);


struct ldl_node_t ldl_ctx_resolve_node(ldl_ctx_t * ctx, const char * node_path);
struct ldl_node_t ldl_ctx_get_root_node();

int32_t 		  ldl_node_num_children();
int32_t           ldl_node_get_child();
struct ldl_node_t ldl_node_get_child_by_name();


int32_t ldl_node_is_string();
int32_t ldl_node_is_number();
int32_t ldl_node_is_table();
int32_t ldl_node_is_function();

const char * ldl_node_to_string();
double       ldl_node_to_number();
int32_t 	 ldl_node_execute_function();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __LDL_H__
