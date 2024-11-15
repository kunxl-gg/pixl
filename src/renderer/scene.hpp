#ifndef PIXL_SCENE_HPP
#define PIXL_SCENE_HPP

#include "pixl/src/core/camera.hpp"
#include "pixl/src/core/model.hpp"

#include "pixl/src/renderer/lights.hpp"

namespace pixl {

class Scene {
public:
    LightSettings *getLights() { return _lights; }

    std::vector<Model *> &getModels() { return _models; }
    void addModel(Model *model) { _models.push_back(model); }

    void setupLights();
    void setupCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
private:
    Camera *_camera;
    LightSettings *_lights;
    std::vector<Model *> _models;
};

} // namespace pixl

#endif // PIXL_SCENE_HPP
