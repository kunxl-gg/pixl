#ifndef PIXL_RENDERER_HPP
#define PIXL_RENDERER_HPP

#include "pixl/src/core/camera.hpp"

#include "pixl/src/renderer/scene.hpp"
#include "pixl/src/renderer/techniques/blinn-phong.hpp"

namespace pixl {

class Renderer {
public:
    Renderer();

    void render(Scene *scene);
private:
    Camera *_camera;

    BlinnPhong *_blinnPhong;
};

} // namespace pixl

#endif // PIXL_RENDERER_HPP
