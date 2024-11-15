#include "pixl/src/core/window.hpp"
#include "pixl/src/core/debug.hpp"

namespace pixl {

Window::Window(const char *title) {
    if (!glfwInit()) {
        error("Failed to initialise GLFW");
        return;
    }

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    _title = title;
    _width = mode->width;
    _height = mode->height;
    _window = nullptr;
}

Window::Window(int width, int height, const char *title) {
    if (!glfwInit()) {
        error("Failed to initialise GLFW");
        return;
    }

    _title = title;
    _width = width;
    _height = height;
    _window = nullptr;
}

Window::~Window() {
    shutdown();
}

void Window::init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    glfwMakeContextCurrent(_window);

    info("Created window: %s (%d x %d)", _title, _width, _height);
    glfwSetFramebufferSizeCallback(_window, handleResize);
}

void Window::shutdown() {
    glfwDestroyWindow(_window);
}

void Window::handleResize(GLFWwindow *window, int width, int height) {
    info("Resized Viewport: (%d x %d)", width, height);
    glViewport(0, 0, width, height);
}

void Window::resize(int width, int height) {
    _width = width;
    _height = height;

    info("Resized window: %s (%d x %d)", _title, _width, _height);
    glViewport(0, 0, _width, _height);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(_window);
}

void Window::stopRunning() {
    glfwSetWindowShouldClose(_window, true);
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
