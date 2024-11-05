#ifndef PIXL_APPLICATION_HPP
#define PIXL_APPLICATION_HPP

#include "pixl/src/core/window.hpp"
#include "pixl/src/renderer/renderer.hpp"
#include "pixl/src/renderer/scene.hpp"

namespace pixl {

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void run();
    void shutdown();

    Window &getWindow() { return *_window; }

    void setupScene();
private:
    bool _isRunning;

    Scene *_scene = nullptr;
    Window *_window = nullptr;
    Renderer *_renderer = nullptr;
};

extern Engine app;

} // namespace pixl

#endif // PIXL_APPLICATION_HPP
