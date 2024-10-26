#version 400 core

in vec2 TexCoords;
uniform sampler2D texture1;

// Output Variables
out vec4 FragColor;

void main() {
    FragColor = vec4(texture(texture1, TexCoords).rgb, 1.0f);
}
