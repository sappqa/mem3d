#version 330 core

uniform mat4 u_proj = mat4(1.0);
 
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 fragcolor;

void main() {
    gl_Position = u_proj * vec4(position, 1.0);
    fragcolor = color;
}