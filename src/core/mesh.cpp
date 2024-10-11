#include "pixl/src/core/mesh.hpp"

namespace pixl {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices) {
    _vertices = vertices;
    _indices = indices;

    _vao = VertexArray();
    _vbo = VertexBuffer();
    _ebo = VertexBuffer();

    setupMesh();
}

void Mesh::setupMesh() {
    _vao.bind();

    _vbo.bind(GL_ARRAY_BUFFER);
    _vbo.setData(GL_ARRAY_BUFFER, _vertices.data(), _vertices.size() * sizeof(Vertex));

    _ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    _ebo.setData(GL_ELEMENT_ARRAY_BUFFER, _indices.data(), _indices.size() * sizeof(int));

    _vao.setAttrib(0, 3, offsetof(Vertex, _position));
    _vao.setAttrib(1, 3, offsetof(Vertex, _normal));
    _vao.setAttrib(2, 2, offsetof(Vertex, _uv));

    _vbo.unbind(GL_ARRAY_BUFFER);
    _vao.unbind();
}


void Mesh::draw(Shader &shader) {
    _vao.bind();
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    _vao.unbind();
}

} // namespace pixl
