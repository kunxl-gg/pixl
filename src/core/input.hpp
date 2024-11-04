#ifndef PIXL_INPUTS_H
#define PIXL_INPUTS_H

#include "pixl/include/GLFW/glfw3.h"
#include "pixl/include/glm/glm.hpp"

namespace pixl {

class Input {
public:
    static bool isKeyPressed(int key);

    static void getCursorPosition(double &x, double &y);
    static void setCursorPosition(double x, double y);
private:
};

} // namespace pixl

#endif // PIXL_INPUTS_H
