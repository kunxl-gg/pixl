#ifndef PIXL_TEXTURE_H
#define PIXL_TEXTURE_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

enum TextureType {
    kAmbient,
    kDiffuse,
    kSpecular,
};

class Texture {
public:
    Texture(const std::string &path, TextureType type);

    void bind();
    void unbind();

    void loadTexture(GLenum format = GL_RGB);
private:
    GLuint _textureID;
    TextureType _type = kDiffuse;

    int _width;
    int _height;
    int _numChannels;

    const char *_path;
};

} // namespace pixl

#endif // PIXL_TEXTURE_H

