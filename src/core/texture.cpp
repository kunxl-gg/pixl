#define STB_IMAGE_IMPLEMENTATION
#include "pixl/include/stb_image.h"
#include "pixl/src/core/texture.hpp"

namespace pixl {

Texture::Texture(const std::string &path, TextureType type) {
    _path = path.c_str();
    _type = type;
    _textureID = 0;
    _width = 0;
    _height = 0;

    loadTexture();
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture(GLenum format) {
    unsigned char *data = stbi_load(_path, &_width, &_height, &_numChannels, 0);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);

    // Configure parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load Texture!");
    }

    stbi_image_free(data);
}

} // namespace pixl
