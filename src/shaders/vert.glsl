#version 400 core

// Input Variables
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 aNormals;

// Uniform Variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Output Variables
out vec3 FragPos;
out vec3 Normal;

void main() {
    FragPos = vec3(model * vec4(apos, 1.0f));
    Normal = aNormals;
    gl_Position = projection * view * model * vec4(apos, 1.0f);
}
