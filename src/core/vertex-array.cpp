#include "pixl/src/core/vertex-buffer.hpp"
#include "pixl/src/core/vertex-array.hpp"

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

void VertexArray::setAttrib(int id, int size, int offset) {
    glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(id);
}

}
