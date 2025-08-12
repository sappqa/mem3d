#include "shaders.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static char* _shader_read_source(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("error: unable to open shader source file");
    }

    size_t buf_len = 2048;
    char* buf = (char*)malloc(2048);
    int len = read(fd, buf, buf_len - 1);
    if (len == -1) {
        perror("error: unable to read shader source file");
        close(fd);
    }

    buf[len] = '\0';
    close(fd);
    return buf;
}

GLuint shaders_init() {
    char* vertex_shader_source = _shader_read_source("../resources/shaders/simple_color.vert");
    char* fragment_shader_source = _shader_read_source("../resources/shaders/simple_color.frag");

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLint success;
    GLchar vsInfoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, sizeof(vsInfoLog), NULL, vsInfoLog);
        fprintf(stderr, "error: vertex shader compilation failed: \n%s\n", vsInfoLog);
    }
 
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    GLchar fsInfoLog[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, sizeof(fsInfoLog), NULL, fsInfoLog);
        fprintf(stderr, "error: fragment shader compilation failed: \n%s\n", fsInfoLog);
    }
 
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLchar infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    free(vertex_shader_source);
    free(fragment_shader_source);

    return program;
}