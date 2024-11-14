#version 330 core

in vec3 vPos;
out vec3 iFrag;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 vCol;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    iFrag = vCol;
}