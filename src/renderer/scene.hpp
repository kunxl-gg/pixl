#ifndef PIXL_SCENE_HPP
#define PIXL_SCENE_HPP

#include "pixl/src/core/camera.hpp"
#include "pixl/src/core/model.hpp"

namespace pixl {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    std::vector<Model *> &getModels() { return _models; }
    void addModel(Model *model) { _models.emplace_back(model); }

    void activateShader() { _shader.use(); }
    void deactivateShader() { glUseProgram(0); }
    void setShader(const std::string &vertexPath, const std::string &fragmentPath) {
        _shader = Shader(vertexPath, fragmentPath);
    }

    void setModelMatrix(const glm::mat4 &model) { _shader.setMat4("model", model); }
    void setViewMatrix(const glm::mat4 &view) { _shader.setMat4("view", view); }
    void setProjectionMatrix(const glm::mat4 &projection) { _shader.setMat4("projection", projection); }
private:
    Shader _shader;
    std::vector<Model *> _models;
};

} // namespace pixl

#endif // PIXL_SCENE_HPP
