#ifndef PIXL_TEXTURE_H
#define PIXL_TEXTURE_H

#include <glad/glad.h>
#include <string>

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

