#include "pixl/src/core/render.hpp"
#include "pixl/src/core/shaders.hpp"
#include <fstream>

namespace pixl {

Render::Render(const std::string &vshader, const std::string &fshader) {
    _shader = Shader(vshader, fshader);

    _VAO = VertexArray();
    _VBO = VertexBuffer();
    _EBO = VertexBuffer();
}

void Render::render(const std::string &path, glm::vec3 position, glm::vec3 scale,
                    glm::vec3 rotation) {

}

void Render::loadVertices(const std::string &path, float *vertices) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    float vertex;
    while (file >> vertex) {
        *vertices = vertex;
        vertices++;
    }
}

} // namespace pixl
