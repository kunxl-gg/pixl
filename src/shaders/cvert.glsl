#version 400 core

layout (location = 0) in vec3 apos;
out vec3 TexCoords;

// Uniform Variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    TexCoords = apos;
    gl_Position = vec4(apos, 1.0f);
}
