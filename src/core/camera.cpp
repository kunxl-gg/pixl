#include "pixl/src/core/camera.hpp"

namespace pixl {

Camera::Camera(const glm::vec3 position, glm::vec3 front, glm::vec3 up) {
    _cameraPos = position;
    _cameraFront = front;
    _cameraUp = up;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

void Camera::processKeyboard(CameraMovement direction) {
    if (direction == CameraMovement::kForward) {
        _cameraPos += _cameraFront * 0.05f;
    } else if (direction == CameraMovement::kBackward) {
        _cameraPos -= _cameraFront * 0.05f;
    } else if (direction == CameraMovement::kLeft) {
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * 0.05f;
    } else if (direction == CameraMovement::kRight) {
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * 0.05f;
    }
}

} // namespace pixl
