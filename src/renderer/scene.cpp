#include "pixl/src/renderer/scene.hpp"
#include "pixl/src/core/camera.hpp"

namespace pixl {

void Scene::setupCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) {
    _camera = new Camera(cameraPos, cameraFront, cameraUp);
}

void Scene::setupLights() {

}

} // namespace pixl
