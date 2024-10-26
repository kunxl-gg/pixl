#include "pixl/src/core/frame-buffer.hpp"

namespace pixl {

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &_fbo);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &_fbo);
}

void FrameBuffer::create(int width, int height) {
    _width = width;
    _height = height;
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::resize(int width, int height) {
    _width = width;
    _height = height;
}

void FrameBuffer::attachTexture(GLenum attachment, GLuint textureId) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureId, 0);
}

void FrameBuffer::attachRenderBuffer() {
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);
}

} // namespace pixl
