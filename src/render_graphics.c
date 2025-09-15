#include "render_graphics.h"
#include "common.h"
#include "shaders.h"
#include "orbit_camera.h"
#include "glad/glad.h"
#include "animation_timer.h"
#include "stdint.h"
#include "stdio.h"

static GLuint _simple_shaders;
static GLuint _vao_cube;
static GLuint _vao_grid;
static GLuint _vbo_cube_vertices;
static GLuint _vbo_cube_colors;
static GLuint _vbo_grid_vertices;
static GLuint _vbo_grid_colors;
static GLuint _ebo;
static int _grid_size = 20;
static int _u_proj_location;
static uint64_t frame_number = 0;

memory_event* _memory_events;
size_t _num_memory_events;
// memory_event_bounds _memory_events_bounds;

static void _shaders_init() {
    _simple_shaders = shaders_init();
    glUseProgram(_simple_shaders);
    _u_proj_location = glGetUniformLocation(_simple_shaders, "u_proj");
    glUseProgram(0);
}

static void _vertices_init() {

    float cube_vertices[] = {
        -1.0f, -1.0f, -1.0f,   
        1.0f, -1.0f, -1.0f,   
        1.0f, 1.0f, -1.0f,   
        -1.0f, 1.0f, -1.0f,   

        -1.0f, -1.0f, 1.0f,   
        1.0f, -1.0f, 1.0f,   
        1.0f, 1.0f, 1.0f,   
        -1.0f, 1.0f, 1.0f,   
    };

    float cube_colors[] = {
        0.6f, 0.1f, 0.1f, 1.0f,
        0.6f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.6f, 1.0f,
        0.1f, 0.1f, 0.6f, 1.0f,

        0.1f, 0.6f, 0.1f, 1.0f,
        0.1f, 0.6f, 0.1f, 1.0f,
        0.6f, 0.1f, 0.6f, 1.0f,
        0.6f, 0.1f, 0.6f, 1.0f
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
    
    for (int i = -_grid_size / 2; i <= _grid_size / 2; i++) {
        // horizontal line
        grid_vertices[index_vertices++] = -_grid_size / 2;
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;

        grid_vertices[index_vertices++] = _grid_size / 2;
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;
    }

    for (int i = -_grid_size / 2; i <= _grid_size / 2; i++) {
        // vertical line
        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = -_grid_size / 2;
        grid_vertices[index_vertices++] = 0.0f;

        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 0.3f;
        grid_colors[index_colors++] = 1.0f;

        grid_vertices[index_vertices++] = i;
        grid_vertices[index_vertices++] = _grid_size / 2;
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
    orbit_camera_init();
}

static void _animation_init(memory_event* memory_events, size_t num_memory_events, memory_event_bounds* bounds) {
    uint64_t process_start_timestamp = timespec_to_nanoseconds(&bounds->start_timestamp);
    uint64_t process_end_timestamp = timespec_to_nanoseconds(&bounds->end_timestamp);
    uint64_t process_total_runtime = process_end_timestamp - process_start_timestamp;
    uint32_t animation_duration = animation_timer_get_animation_duration_ms();

    for (int i = 0; i < num_memory_events; i++) {
        uint64_t mem_event_ts = timespec_to_nanoseconds(&memory_events[i].timestamp);
        double progress = (double)(mem_event_ts - process_start_timestamp) / (double)process_total_runtime;
        memory_events[i].animation_timestamp = progress * animation_duration;
    }

    _num_memory_events = num_memory_events;
    _memory_events = memory_events;
}

void graphics_init(memory_event* memory_events, size_t num_memory_events, memory_event_bounds* bounds) {
    _shaders_init();
    _vertices_init();
    _camera_init();
    _animation_init(memory_events, num_memory_events, bounds);

    glEnable(GL_DEPTH);
}


/*
for now, have global animation frame number. to restart the animation, set the frame number back to 0
given the frame number, and the current memory event's real-time interpolated timestamp, if frame == event.timestamp, if alloc, add to render list. if free, remove from render list

then render the render list
*/
void render_graphics() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_simple_shaders);
    mat4x4 proj;
    orbit_camera_get_projection(proj);
    glUniformMatrix4fv(_u_proj_location, 1, 0, (GLfloat*)proj);

    glBindVertexArray(_vao_cube);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(_vao_grid);
    glDrawArrays(GL_LINES, 0, (_grid_size + 1) * 2 * 2 + 2);

    glBindVertexArray(0);
    glUseProgram(0);

    frame_number++;
}