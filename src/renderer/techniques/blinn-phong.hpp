#ifndef PIXL_TECHNIQUES_BLINN_PHONG
#define PIXL_TECHNIQUES_BLINN_PHONG

#include "pixl/src/core/shaders.hpp"
namespace pixl {

class BlinnPhong {
public:
    BlinnPhong();
    ~BlinnPhong();

    void use();
    void init(std::string vShader, std::string fShader);
private:
    Shader *_shaders;
};

} // namespace pixl

#endif // PIXL_TECHNIQUES_BLINN_PHONG
