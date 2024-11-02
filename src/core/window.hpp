#ifndef PIXL_WINDOW_HPP
#define PIXL_WINDOW_HPP

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();

    void init();
    void shutdown();

    static void handleResize(GLFWwindow *window, int width, int height);
    void resize(int width, int height);
    void setViewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    void beginFrame();
    void endFrame();

    bool isRunning();
    void stopRunning();

    GLFWwindow *getWindow() { return _window; }
private:
    GLFWwindow *_window;
    int _width, _height;
    const char *_title;
};

} // namespace pixl

#endif // PIXL_WINDOW_HPP
