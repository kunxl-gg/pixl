#version 400 core

// Input Variables
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoord;

// Output Variables
out vec2 TexCoords;

void main() {
    TexCoords = aTexCoord;
    gl_Position = vec4(apos, 1.0f);
}
