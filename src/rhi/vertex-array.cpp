#include "pixl/src/core/mesh.hpp"
#include "pixl/src/rhi/vertex-array.hpp"

namespace pixl {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &_VAO);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &_VAO);
}

void VertexArray::bind() {
    glBindVertexArray(_VAO);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::setAttrib(int id, size_t size, size_t stride, size_t offset) {
    glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
    glEnableVertexAttribArray(id);
}

}
