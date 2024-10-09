#ifndef PIXL_TEXTURE_H
#define PIXL_TEXTURE_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class Texture {
public:
    Texture(const std::string &path);

    void bind();
    void unbind();

    void loadTexture();
private:
    GLuint _textureID;

    int _width;
    int _height;
    int _numChannels;

    const char *_path;
};

} // namespace pixl

#endif // PIXL_TEXTURE_H

