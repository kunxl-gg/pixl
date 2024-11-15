#version 400 core

// Input variables
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Uniform variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Output Variables
out vec3 Normals;

void main() {
    Normals = normal;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}
