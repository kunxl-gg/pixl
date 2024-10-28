#include "pixl/src/core/application.hpp"

namespace pixl {

Application::Application() {
    _window = nullptr;
    _isRunning = false;
}

Application::~Application() {
    shutdown();
}

void Application::init() {
    // Initialise the window
    _window = new Window(800, 600, "Pixl");
    _window->init();

    _isRunning = true;
}

void Application::shutdown() {
    delete _window;
    _window = nullptr;
}

void Application::run() {
    init();

    while (_isRunning) {
        _window->beginFrame();
        _window->endFrame();

        _isRunning = _window->isRunning();
    }

    shutdown();
}

} // namespace pixl
