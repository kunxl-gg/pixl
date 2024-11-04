#include "pixl/src/renderer/renderer.hpp"

namespace pixl {

void Renderer::render(Scene &scene) {
    scene.activateShader();
    for (Model *model: scene.getModels()) {
        model->drawModel();
    }
}

} // namespace pixl
