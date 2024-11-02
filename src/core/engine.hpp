#ifndef PIXL_APPLICATION_HPP
#define PIXL_APPLICATION_HPP

#include "pixl/src/core/window.hpp"

namespace pixl {

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void run();
    void shutdown();

    Window &getWindow() { return *_window; }
private:
    Window *_window;
    bool _isRunning;
};

extern Engine app;

} // namespace pixl

#endif // PIXL_APPLICATION_HPP
