#ifndef PIXL_MESH_HPP
#define PIXL_MESH_HPP

#include "pixl/src/pixl-precomp.hpp"

#include "pixl/src/core/shaders.hpp"
#include "pixl/src/core/vertex-array.hpp"
#include "pixl/src/core/vertex-buffer.hpp"

namespace pixl {

struct Vertex {
    glm::vec3 _position;
    glm::vec3 _normal;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<int> indices);

    void setupMesh();
    void draw(Shader &shader);
private:
    std::vector<int> _indices;
    std::vector<Vertex> _vertices;

    VertexBuffer _ebo;
    VertexBuffer _vbo;
    VertexArray _vao;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

} // namespace pixl

#endif //PIXEL_MESH_HPP
