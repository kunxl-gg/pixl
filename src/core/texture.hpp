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
    Texture(TextureType type, int widht, int height);

    void bind();
    void unbind();

    void loadTexture(GLenum format = GL_RGB);

    GLuint getTexID() { return _textureID; }
    void clear();
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

