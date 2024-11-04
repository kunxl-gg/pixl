#include "pixl/src/core/engine.hpp"
#include "pixl/src/core/input.hpp"
#include "pixl/src/core/model.hpp"

namespace pixl {

Engine::Engine() {
    _window = nullptr;
    _isRunning = false;
    _camera = Camera();
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

    // Initialise the camera
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    _camera = Camera(cameraPos, cameraFront, cameraUp);

    // Initialise the renderer
    _renderer = Renderer();

    // Setup the scene
    setupScene();
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

        _renderer.render(_scene);

        _isRunning = _window->isRunning();

        _window->endFrame();
    }

    shutdown();
}

void Engine::setupScene() {
     _scene = Scene();

    Model bunny("/Users/kunaltiwari/pixl/assets/stanford-bunny.obj");
    _scene.addModel(&bunny);

    _scene.setShader("/Users/kunaltiwari/pixl/src/shaders/vert.glsl", "/Users/kunaltiwari/pixl/src/shaders/frag.glsl");
    _scene.activateShader();
    _scene.setModelMatrix(glm::mat4(1.0f));
    _scene.setViewMatrix(_camera.getViewMatrix());
    _scene.setProjectionMatrix(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

    _scene.deactivateShader();
}

} // namespace pixl
