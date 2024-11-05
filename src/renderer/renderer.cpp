#include "pixl/src/renderer/renderer.hpp"
#include "pixl/src/renderer/techniques/blinn-phong.hpp"

namespace pixl {

Renderer::Renderer() {
    _blinnPhong = new BlinnPhong();
    _blinnPhong->init("src/shaders/blinn-phong/vert.glsl", "src/shaders/blinn-phong/frag.glsl");
}

void Renderer::render(Scene *scene) {
    _blinnPhong->use();

    for (Model *model: scene->getModels()) {
        model->drawModel();
    }
}

} // namespace pixl
