add_library(hooks SHARED mem_hooks.c)

target_include_directories(hooks PRIVATE ${CMAKE_SOURCE_DIR}/src)