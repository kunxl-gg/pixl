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
    void resize(int width, int height);

    void beginFrame();
    void endFrame();

    void isRunning();
private:
    GLFWwindow *_window;
    int _width, _height;
    const char *_title;
};

} // namespace pixl

#endif // PIXL_WINDOW_HPP
