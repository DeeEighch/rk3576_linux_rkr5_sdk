cmake_minimum_required( VERSION 2.8.8 )

set(RT_ARGPARSE_SRC
	argparse.c
	)

set_source_files_properties(
	argparse.c
	PROPERTIES
	COMPILE_FLAGS "-Wno-error=restrict"
	)

add_library(${LIB_STATIC_ARGPARSE} STATIC ${RT_ARGPARSE_SRC})
set_target_properties(${LIB_STATIC_ARGPARSE} PROPERTIES FOLDER "rt_argparse")
target_link_libraries(${LIB_STATIC_ARGPARSE})
