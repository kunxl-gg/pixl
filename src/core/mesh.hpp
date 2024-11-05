#ifndef PIXL_MESH_HPP
#define PIXL_MESH_HPP

#include "pixl/src/pixl-precomp.hpp"

#include "pixl/src/core/shaders.hpp"
#include "pixl/src/core/texture.hpp"

#include "pixl/src/rhi/vertex-array.hpp"
#include "pixl/src/rhi/vertex-buffer.hpp"

namespace pixl {

struct Vertex {
    glm::vec3 _position;
    glm::vec3 _normal;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<int> indices);

    void setupMesh();
    void draw();

    std::vector<Vertex> _vertices;
private:
    std::vector<int> _indices;
    std::vector<Texture *> _textures;

    VertexBuffer *_ebo;
    VertexBuffer *_vbo;
    VertexArray *_vao;
};

} // namespace pixl

#endif //PIXEL_MESH_HPP
