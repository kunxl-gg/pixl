#include "pixl/include/stb_image.h"
#include "pixl/src/core/cubemap.hpp"
#include "pixl/src/core/debug.hpp"

namespace pixl {

CubeMap::CubeMap() {
    glGenTextures(1, &_textureId);
}

CubeMap::~CubeMap() {
    glDeleteTextures(1, &_textureId);
}

void CubeMap::bind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);
}

void CubeMap::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::load(const std::string path[6]) {
    bind();

    int width, height;
    int nChannels;
    for (int i = 0; i < 6; i++) {
        unsigned char *data = stbi_load(path[i].c_str(), &width, &height, &nChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            error("CubeMap tex failed to laod at path %s", path[i].c_str());
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    unbind();
}

} // namespace pixl
