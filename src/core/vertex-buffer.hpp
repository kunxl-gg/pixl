#ifndef PIXL_VERTEX_BUFFER_H
#define PIXL_VERTEX_BUFFER_H

#include "pixl/src/pixl-precomp.hpp"

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
