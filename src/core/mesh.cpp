#include "pixl/src/core/mesh.hpp"

namespace pixl {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices) {
    _vertices = vertices;
    _indices = indices;

    _vbo = new VertexBuffer();
    _ebo = new VertexBuffer();
    _vao = new VertexArray();

    setupMesh();
}

void Mesh::setupMesh() {
    _vao->bind();

    // load data into vertex buffers
    _vbo->bind(GL_ARRAY_BUFFER);
    _vbo->setData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0]);

    // load data into element buffers
    _ebo->bind(GL_ELEMENT_ARRAY_BUFFER);
    _ebo->setData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(int), &_indices[0]);

    // set the vertex attribute pointers
    _vao->setAttrib(0, 3, sizeof(Vertex), 0);
    _vao->setAttrib(1, 3, sizeof(Vertex), offsetof(Vertex, _normal));

    // unbind the VBO and VAO
    _vbo->unbind(GL_ARRAY_BUFFER);
    _vao->unbind();
}


void Mesh::draw() {
    _vao->bind();
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    _vao->unbind();
}

} // namespace pixl
