#ifndef PIXL_VERTEX_ARRAY_H
#define PIXL_VERTEX_ARRAY_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    GLuint getID() { return _VAO; }

    void bind();
    void unbind();

    void setAttrib(int id, int size, int offset, int stride = 8);
    void setAttribn(int id, int offset);
private:
    GLuint _VAO;
};

} // namespace pixl

#endif // !PIXL_VERTEX_ARRAY_H
