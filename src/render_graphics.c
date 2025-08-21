#include "render_graphics.h"
#include "common.h"
#include "shaders.h"
#include "linmath.h"
#include "glad/glad.h"

#include <unistd.h>
#include <stdio.h>

static GLuint _simple_shaders;
static GLuint _vao_cube;
static GLuint _vao_grid;
static GLuint _vbo_cube_vertices;
static GLuint _vbo_cube_colors;
static GLuint _vbo_grid_vertices;
static GLuint _vbo_grid_colors;
static GLuint _ebo;
static int _grid_size = 20;

static void _vertices_init() {

    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f,   
        1.0f, 0.0f, 0.0f,   
        1.0f, 1.0f, 0.0f,   
        0.0f, 1.0f, 0.0f,   

        0.0f, 0.0f, 1.0f,   
        1.0f, 0.0f, 1.0f,   
        1.0f, 1.0f, 1.0f,   
        0.0f, 1.0f, 1.0f,   
    };

    float cube_colors[] = {
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,

        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f
    };

    GLuint indices[] = {
        1, 3, 0, // bottom
        1, 2, 3,

        5, 7, 6, // top
        5, 4, 7,

        0, 4, 3, // left
        4, 7, 3,

        1, 2, 6, // right
        1, 6, 5,

        3, 2, 6, // back
        3, 6, 7,

        0, 1, 5, // front
        0, 5, 4,
    };

    float grid_vertices[(_grid_size + 1) * 2 * 6];
    float grid_colors[(_grid_size + 1) * 2 * 8];
    int index_vertices = 0;
    int index_colors = 0;
    
    for (int i = 0; i <= _grid_size; i++) {
        // horizontal line
        grid_vertices[index_vertices++] = 0.0f;
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;

        grid_vertices[index_vertices++] = _grid_size;
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;

        // // vertical line
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = 0.0f;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;

        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = _grid_size;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;
    }

    glGenBuffers(1, &_vbo_cube_vertices);
    glGenBuffers(1, &_vbo_cube_colors);
    glGenBuffers(1, &_ebo);

    glGenVertexArrays(1, &_vao_cube);
    glBindVertexArray(_vao_cube);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_cube_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &_vbo_grid_vertices);
    glGenBuffers(1, &_vbo_grid_colors);
    glGenVertexArrays(1, &_vao_grid);
    glBindVertexArray(_vao_grid);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_grid_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grid_vertices), grid_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_grid_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grid_colors), grid_colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void _camera_init() {
    // init camera to center of grid
    vec3 eye = {10.1, -7.0, 30};
    vec3 target = {10, 10, 0};
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

    glEnable(GL_DEPTH);
}

void render_graphics() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_simple_shaders);
    glBindVertexArray(_vao_cube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(_vao_grid);
    glDrawArrays(GL_LINES, 0, (_grid_size + 1) * 2 * 2 + 2);
    glBindVertexArray(0);
    glUseProgram(0);
}