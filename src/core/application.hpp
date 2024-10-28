#ifndef PIXL_APPLICATION_HPP
#define PIXL_APPLICATION_HPP

#include "pixl/src/core/window.hpp"
namespace pixl {

class Application {
public:
    Application();
    ~Application();

    void init();
    void run();
    void shutdown();
private:
    Window *_window;
    bool _isRunning;
};

} // namespace pixl

#endif // PIXL_APPLICATION_HPP
