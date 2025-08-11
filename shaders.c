#pragma once
#include "glad/glad.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char* _shader_read_source(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("error: unable to open shader source file");
    }

    char* buf = (char*)malloc(2048);
    int len = read(fd, buf, sizeof(buf) - 1);
    if (len == -1) {
        perror("error: unable to read shader source file");
        close(fd);
    }

    buf[len] = '\0';
    close(fd);
    return buf;
} 

void shaders_init() {
    char* vertex_shader_source = _shader_read_source("../resources/shaders/simple_color.vert");
    char* fragment_shader_source = _shader_read_source("../resources/shaders/simple_color.frag");
    
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
 
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
 
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    free(vertex_shader_source);
    free(fragment_shader_source);
}