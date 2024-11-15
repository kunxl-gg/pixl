#include "pixl/src/renderer/scene.hpp"
#include "pixl/src/core/camera.hpp"

namespace pixl {

Scene::Scene() {
    _camera = new Camera();
    _lights = new LightSettings();
}

Scene::~Scene() {
    delete _camera;
    delete _lights;
}

void Scene::setupCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) {
    _camera = new Camera(cameraPos, cameraFront, cameraUp);
}

} // namespace pixl
