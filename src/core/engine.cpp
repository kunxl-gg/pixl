#include "pixl/src/core/engine.hpp"
#include "pixl/src/core/input.hpp"
#include "pixl/src/core/model.hpp"

namespace pixl {

Engine::Engine() {
    _window = nullptr;
    _isRunning = false;

    // Initialise the camera
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    _camera = Camera(cameraPos, cameraFront, cameraUp);
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
    _renderer = new Renderer();

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
        } else if (Input::isKeyPressed(GLFW_KEY_W)) {
            _camera.processKeyboard(CameraMovement::kForward);
        } else if (Input::isKeyPressed(GLFW_KEY_S)) {
            _camera.processKeyboard(CameraMovement::kBackward);
        } else if (Input::isKeyPressed(GLFW_KEY_A)) {
            _camera.processKeyboard(CameraMovement::kLeft);
        } else if (Input::isKeyPressed(GLFW_KEY_D)) {
            _camera.processKeyboard(CameraMovement::kRight);
        }

        _renderer->render(_scene);

        _isRunning = _window->isRunning();

        _window->endFrame();
    }

    shutdown();
}

void Engine::setupScene() {
     _scene = Scene();

    Model *bunny = new Model(std::filesystem::absolute("assets/teapot.obj"));
    _scene.addModel(bunny);
}

} // namespace pixl
