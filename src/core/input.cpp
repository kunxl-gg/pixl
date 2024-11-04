#include "pixl/src/core/engine.hpp"
#include "pixl/src/core/input.hpp"

namespace pixl {

bool Input::isKeyPressed(int key) {
    return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}

void Input::getCursorPosition(double &x, double &y) {
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
}

} // namespace pixl


