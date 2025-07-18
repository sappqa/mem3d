cmake_minimum_required(VERSION 3.15)
project(mem3d LANGUAGES C)

add_executable(${PROJECT_NAME} main.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE _POSIX_C_SOURCE=200112L)