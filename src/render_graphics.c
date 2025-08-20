#include "render_graphics.h"
#include "common.h"
#include "shaders.h"
#include "linmath.h"
#include "glad/glad.h"

static GLuint _simple_shaders;
static GLuint _vao;
static GLuint _vbo;
static GLuint _ebo;

static void _vertices_init() {

    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 0.2f, 0.2f, 1.0f,
        1.0f, 0.0f, 0.0f,   1.0f, 0.2f, 0.2f, 1.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 0.2f, 0.2f, 1.0f,
        0.0f, 1.0f, 0.0f,   1.0f, 0.2f, 0.2f, 1.0f,

        0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 1.0f,
    };

    int indices[] = {
        1, 3, 0, // bottom
        1, 2, 3,

        5, 6, 7, // top
        7, 4, 5,

        0, 4, 3, // left
        4, 7, 3,

        1, 2, 6, // right
        1, 6, 5,

        3, 2, 6, // back
        3, 6, 7,

        0, 1, 5, // front
        0, 5, 4,
    };

    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void _camera_init() {
    vec3 eye = {-1.1, -7, 4};
    vec3 target = {1, 1, 0};
    vec3 up = {0, 0, 1};
    mat4x4 view, perspective, proj;
    mat4x4_look_at(view, eye, target, up);
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, view);

    glUseProgram(_simple_shaders);
    int proj_loc = glGetUniformLocation(_simple_shaders, "u_proj");
    glUniformMatrix4fv(proj_loc, 1, 0, (GLfloat*)proj);
    glUseProgram(0);
}

void graphics_init() {
    _simple_shaders = shaders_init();
    _vertices_init();
    _camera_init();
}

void render_graphics() {
    glClearColor(0.3f, 0.23f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_simple_shaders);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}