#include "render_graphics.h"
#include "shaders.h"
#include "linmath.h"
#include "glad/glad.h"

static GLuint _simple_shaders;
static GLuint _vao;
static GLuint _vbo;

static void _vertices_init() {
    float vertices[] = {
        -0.5f, -0.5, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.5, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f, 
    };

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 3));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void graphics_init() {
    _simple_shaders = shaders_init();
    _vertices_init();
}

void render_graphics() {
    glClearColor(0.3f, 0.23f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_simple_shaders);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);


}