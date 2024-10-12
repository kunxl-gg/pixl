#include "pixl/src/core/vertex-buffer.hpp"

namespace pixl {

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &_VBO);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_VBO);
}

void VertexBuffer::bind(GLenum target) {
    glBindBuffer(target, _VBO);
}

void VertexBuffer::unbind(GLenum target) {
    glBindBuffer(target, 0);
}

void VertexBuffer::setData(GLenum target, size_t size, const void *data) {
    glBindBuffer(target, _VBO);
    glBufferData(target, size, data, GL_STATIC_DRAW);
}

} // namespace pixl
