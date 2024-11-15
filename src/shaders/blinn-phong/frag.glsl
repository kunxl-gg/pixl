#version 400 core

struct pointLight {
    vec3 color;
    vec3 direction;
};

// Input Variables
in vec3 Normals;

// Uniform Variables
uniform pointLight light;

// Output Variables
out vec4 FragColor;

void main() {
    vec3 objColor = vec3(1.0, 0.5, 0.2); // Object color as vec3
    vec3 norm = normalize(Normals);      // Normalize the normal vector
    vec3 lightDir = normalize(light.direction); // Normalize the light direction

    // Diffuse lighting calculation
    float diff = max(dot(norm, lightDir), 0.0); // Clamp to zero if negative

    // Combine object color with light's color and intensity
    vec3 resultColor = objColor * light.color * diff;

    // Set the final fragment color
    FragColor = vec4(resultColor, 1.0); // Alpha set to 1.0 for opaque
}
