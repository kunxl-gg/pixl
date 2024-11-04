#ifndef PIXL_CUBEMAP_HPP
#define PIXL_CUBEMAP_HPP

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class CubeMap {
public:
    CubeMap();
    ~CubeMap();

    void bind();
    void unbind();

    void load(const std::string path[6]);
private:
    GLuint _textureId;
};

} // namespace pixl


#endif // PIXL_CUBEMAP_HPP
