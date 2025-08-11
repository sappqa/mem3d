cmake_minimum_required(VERSION 3.15)
project(mem3d LANGUAGES C)

set(M3D_SOURCES main.c render_window.c render_graphics.c shaders.c thirdparty/glad/src/glad.c)
set(M3D_INCLUDES ${CMAKE_SOURCE_DIR} thirdparty/glad/include thirdparty/linmath/)
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)

include_directories(${M3D_INCLUDES})

add_subdirectory(examples)
add_subdirectory(hooks)

add_executable(${PROJECT_NAME} ${M3D_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE _POSIX_C_SOURCE=200112L)
target_link_libraries(${PROJECT_NAME} glfw)