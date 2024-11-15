#include "pixl/src/renderer/lights.hpp"

namespace pixl {

void LightSettings::setSun(glm::vec3 color, glm::vec3 direction) {
    _hasSun = true;
    _sun._color = color;
    _sun._direction = direction;
}

void LightSettings::addPointLight(glm::vec3 color, glm::vec3 position) {
    PointLight pl;
    pl._color = color;
    pl._position = position;

    _pointLights.push_back(pl);
}

} // namespace pixl
