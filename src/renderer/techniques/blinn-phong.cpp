#include "pixl/src/renderer/techniques/blinn-phong.hpp"

namespace pixl {

BlinnPhong::BlinnPhong() {
}

BlinnPhong::~BlinnPhong() {
}

void BlinnPhong::init(std::string vShader, std::string fShader) {
    std::string vShaderPath = std::filesystem::absolute(vShader);
    std::string fShaderPath = std::filesystem::absolute(fShader);
    _shaders = new Shader(vShaderPath, fShaderPath);

    _shaders->use();
    _shaders->setMat4("model", glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
    _shaders->setMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
}

void BlinnPhong::use() {
    _shaders->use();
}

} // namespace pixl
