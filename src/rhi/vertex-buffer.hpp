#ifndef PIXL_VERTEX_BUFFER_H
#define PIXL_VERTEX_BUFFER_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    int getID() { return _VBO; }

    void bind(GLenum target);
    void unbind(GLenum target);

    void setData(GLenum target, size_t size, const void *data);
private:
    GLuint _VBO;
};

} // namespace pixl

#endif // !PIXL_VERTEX_BUFFER_H
