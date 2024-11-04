#version 400 core

struct Light {
    vec3 _position;
    vec3 _direction;

    vec3 _ambient;
    vec3 _diffuse;
    vec3 _specular;

    float _cutoff;
};

struct Material {
    sampler2D _ambient;
    sampler2D _diffuse;
    float _shininess;
};

// Input Variables
in vec3 Normal;
in vec3 FragPos;

// Uniform Variables
vec3 lightPos = vec3(1.2f, 1.0f, 2.0f)
vec3 viewPos = vec3(0.0f, 0.0f, 0.0f);
bool blingPhong = true;

// Output Variables
out vec4 FragColor;

vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

void main() {
    // Ambient light
    float ambientStrength = 0.1f;
    vec3 ambientColor = ambientStrength * lightColor;

    // Diffuse Light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0.0f) * lightColor;

    // Specular light
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 specular;
    if (blingPhong) {
        float spec = pow(max(dot(norm, halfwayDir), 0.0f), 32.0f);
        specular = specularStrength * spec * lightColor;
    } else {
        float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32.0f);
        specular = specularStrength * spec * lightColor;
    }

    vec3 finalColor = (ambientColor + diffuse + specular) * objectColor;

    FragColor = vec4(finalColor, 1.0f);
}
