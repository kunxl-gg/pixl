#ifndef PIXL_FRAME_BUFFER_HPP
#define PIXL_FRAME_BUFFER_HPP

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class FrameBuffer {
public:
    FrameBuffer();
    ~FrameBuffer();

    void create(int width, int height);
    void bind();
    void unbind();

    void attachTexture(GLenum attachement, GLuint textureId);
    void attachRenderBuffer();

    void resize(int width, int height);

    GLuint getId() const { return _fbo; }
    GLuint getWidth() const { return _width; }
    GLuint getHeight() const { return _height; }

    bool isComplete() const {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
private:
    GLuint _fbo;
    int _width, _height;
};

} // namespace pixl

#endif // PIXL_FRAME_BUFFER_HPP
