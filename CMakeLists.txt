cmake_minimum_required (VERSION 2.6)
project(ldl)
set (ldl_VERSION_MAJOR 1)
set (ldl_VERSION_MINOR 0)

#
# ldl lib file set
#
set(ldl_lib_files
	lib/src/ldl/ldl.c
	lib/src/ldl/ldl.h
)

include_directories(lib/src/)

set(EXECUTABLE_OUTPUT_PATH bin)

#
# ldlread
#
add_executable(ldlread
				${ldl_lib_files}
			    ${ldl_scene_lib_files}
			    tools/ldlread/ldlread.c
			    tools/ldlread/getopt.c
			    tools/ldlread/getopt.c
			    tools/ldlread/getopt_long.c
)
target_link_libraries(ldlread lua)