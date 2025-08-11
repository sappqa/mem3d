#pragma once
#include "render_graphics.h"
#include "glad/glad.h"
#include "linmath.h"

void _read_shader() {
    
}

void graphics_init() {
    float vertices[] = {
        -0.5f, -0.5, -0.5f,     1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5, 0.5f,     1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.5, 0.5f,     1.0f, 1.0f, 0.0f, 1.0f, 
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, sizeof(float) * 3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void render_graphics() {

}