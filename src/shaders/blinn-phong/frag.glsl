#version 400 core

struct directionlight {
    vec3 color;
    vec3 direction;
};

// Input Variables
in vec3 Normals;

// Uniform Variables
uniform directionlight light;

// Output Variables
out vec4 FragColor;

void main() {
    vec3 objColor = vec3(1.0, 0.5, 0.2);
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.direction);

    // Diffuse lighting calculation
    float diff = max(dot(norm, lightDir), 0.0);

    // Combine object color with light's color and intensity
    vec3 resultColor = objColor * light.color * diff;

    // Set the final fragment color
    FragColor = vec4(resultColor, 1.0);
}
