#include "pixl/src/core/window.hpp"
#include "pixl/src/core/debug.hpp"

namespace pixl {

Window::Window(int width, int height, const char *title) {
    _width = width;
    _height = height;
    _title = title;
    _window = nullptr;
}

Window::~Window() {
    shutdown();
}

void Window::init() {
    if (!glfwInit()) {
        error("Failed to initialise GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    glfwMakeContextCurrent(_window);
}

void Window::shutdown() {
    glfwDestroyWindow(_window);
}

void Window::resize(int width, int height) {
    _width = width;
    _height = height;
}

void Window::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Window::endFrame() {
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

} // namespace pixl