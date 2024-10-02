#ifndef PIXL_VERTEX_BUFFER_H
#define PIXL_VERTEX_BUFFER_H

#include <cstddef>
#include <glad/glad.h>

namespace pixl {

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void bind(GLenum target);
    void unbind(GLenum target);

    void setData(GLenum target, const void *data, size_t size);
private:
    GLuint _VBO;
};

} // namespace pixl

#endif // !PIXL_VERTEX_BUFFER_H
