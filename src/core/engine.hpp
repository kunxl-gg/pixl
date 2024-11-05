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
    Window *_window;
    bool _isRunning;

    Scene _scene;
    Camera _camera;
    Renderer *_renderer;
};

extern Engine app;

} // namespace pixl

#endif // PIXL_APPLICATION_HPP
