#ifndef PIXL_CAMERA_H
#define PIXL_CAMERA_H

#include <glm/glm.hpp>

namespace pixl {

enum CameraMovement {
    kForward,
    kBackward,
    kLeft,
    kRight
};

class Camera {
public:
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
