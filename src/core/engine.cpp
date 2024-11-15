#include "pixl/src/core/engine.hpp"
#include "pixl/include/glm/ext/vector_float3.hpp"
#include "pixl/src/core/input.hpp"
#include "pixl/src/core/model.hpp"

namespace pixl {

Engine::Engine() {
    _window = nullptr;
    _isRunning = false;
}

Engine::~Engine() {
    shutdown();
}

void Engine::init() {
    info("Initialising Pixl");

    // Initialise the window
    _window = new Window("Pixl");
    _window->init();

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        error("Failed to initialise GLAD");
        return;
    }

    _window->setViewport();

    // Print OpenGL stats
    info("OpenGL Version: %s", glGetString(GL_VERSION));
    info("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    info("Vendor: %s", glGetString(GL_VENDOR));
    info("Renderer: %s", glGetString(GL_RENDERER));

    // Set the running flag
    _isRunning = true;

    // Initialise the renderer
    _renderer = new Renderer();

    // Setup the scene
    setupScene();
}

void Engine::shutdown() {
    delete _window;
    delete _renderer;
    delete _scene;

    _window = nullptr, _renderer = nullptr, _scene = nullptr;
}

void Engine::run() {
    init();

    while (_isRunning) {
        _window->beginFrame();

        if (Input::isKeyPressed(GLFW_KEY_X)) {
            _window->stopRunning();
        }

        _renderer->render(_scene);

        _isRunning = _window->isRunning();

        _window->endFrame();
    }
}

void Engine::setupScene() {
     _scene = new Scene();

    Model *bunny = new Model(std::filesystem::absolute("assets/teapot.obj"));
    _scene->addModel(bunny);

    _scene->getLights()->setSun(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 0.5f));
}

} // namespace pixl
