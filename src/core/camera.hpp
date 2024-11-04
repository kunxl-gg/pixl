#ifndef PIXL_CAMERA_H
#define PIXL_CAMERA_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

enum CameraMovement {
    kForward,
    kBackward,
    kLeft,
    kRight
};

class Camera {
public:
    Camera() = default;
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);

    glm::mat4 getViewMatrix();
    void processKeyboard(CameraMovement movement);

    glm::vec3 getCameraPos() { return _cameraPos; }

private:
    glm::vec3 _cameraPos;
    glm::vec3 _cameraFront;
    glm::vec3 _cameraUp;
};

} // namespace pixl

#endif // PIXL_CAMERA_H
