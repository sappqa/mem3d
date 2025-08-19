cmake_minimum_required(VERSION 3.15)
project(mem3d LANGUAGES C)

set(M3D_SOURCES ${M3D_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/render_window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/render_graphics.c
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.c
    ${CMAKE_CURRENT_SOURCE_DIR}/memory_event.c
    PARENT_SCOPE)


