#ifndef PIXL_LIGHTS_HPP
#define PIXL_LIGHTS_HPP

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

#define MAX_POINT_LIGHT 512

struct PointLight {
    glm::vec3 _color;
    glm::vec3 _position;
};

struct DirectionalLight {
    glm::vec3 _color;
    glm::vec3 _direction;
};

class LightSettings {
public:
    void setSun(glm::vec3 color, glm::vec3 direction);
    void addPointLight(glm::vec3 color, glm::vec3 position);
private:
    bool _hasSun = false;
    DirectionalLight _sun;
    std::vector<PointLight> _pointLights;
};

} // namespace pixl

#endif // PIXL_LIGHTS_HPP
