#include "pixl/src/core/engine.hpp"
#include "pixl/src/core/input.hpp"

namespace pixl {

Engine::Engine() {
    _window = nullptr;
    _isRunning = false;
}

Engine::~Engine() {
    shutdown();
}

void Engine::init() {
    // Initialise the window
    _window = new Window(800, 600, "Pixl");
    _window->init();

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        error("Failed to initialise GLAD");
        return;
    }

    _window->setViewport(0, 0, 800, 600);

    // Print OpenGL stats
    info("OpenGL Version: %s", glGetString(GL_VERSION));
    info("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    info("Vendor: %s", glGetString(GL_VENDOR));
    info("Renderer: %s", glGetString(GL_RENDERER));

    // Set the running flag
    _isRunning = true;
}

void Engine::shutdown() {
    delete _window;
    _window = nullptr;
}

void Engine::run() {
    init();

    while (_isRunning) {
        _window->beginFrame();

        if (Input::isKeyPressed(GLFW_KEY_X)) {
            _window->stopRunning();
        }

        _isRunning = _window->isRunning();

        _window->endFrame();
    }

    shutdown();
}

} // namespace pixl
