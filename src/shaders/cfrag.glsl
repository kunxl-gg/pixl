#version 400 core

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube texture1;

void main() {
    FragColor = texture(texture1, TexCoords);
}
