#version 330 core

uniform mat4 uProjection = mat4(1.0);
 
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 fragcolor;

void main() {
    gl_Position = uProjection * vec4(position, 1.0);
    fragcolor = color;
}