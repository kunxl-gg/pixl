#include "pixl/src/renderer/renderer.hpp"
#include "pixl/src/core/input.hpp"
#include "pixl/src/renderer/techniques/blinn-phong.hpp"

namespace pixl {

Renderer::Renderer() {
    _blinnPhong = new BlinnPhong();
    _blinnPhong->init("src/shaders/blinn-phong/vert.glsl", "src/shaders/blinn-phong/frag.glsl");

    glm::vec3 cameraPos = glm::vec3(0.0, 0.5, 1.0);
    glm::vec3 cameraFront = glm::vec3(0.0, -0.1, -1.0);
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    _camera = new Camera(cameraPos, cameraFront, cameraUp);

    _blinnPhong->getShader()->setMat4("view", _camera->getViewMatrix());
}

void Renderer::render(Scene *scene) {
    _blinnPhong->use();
    _blinnPhong->getShader()->setMat4("view", _camera->getViewMatrix());

    for (Model *model: scene->getModels()) {
        model->drawModel();
    }

    if (Input::isKeyPressed(GLFW_KEY_W)) {
        _camera->processKeyboard(kForward);
    } else if (Input::isKeyPressed(GLFW_KEY_S)) {
        _camera->processKeyboard(kBackward);
    } else if (Input::isKeyPressed(GLFW_KEY_A)) {
        _camera->processKeyboard(kLeft);
    } else if (Input::isKeyPressed(GLFW_KEY_D)) {
        _camera->processKeyboard(kRight);
    }
}

} // namespace pixl
