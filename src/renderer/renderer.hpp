#ifndef PIXL_RENDERER_HPP
#define PIXL_RENDERER_HPP

#include "pixl/src/renderer/scene.hpp"
namespace pixl {

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void render(Scene &scene);
private:
};

} // namespace pixl

#endif // PIXL_RENDERER_HPP
