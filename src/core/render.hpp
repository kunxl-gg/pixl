#ifndef PIXL_RENDER_HPP
#define PIXL_RENDER_HPP

#include "pixl/src/core/shaders.hpp"
#include "pixl/src/core/vertex-buffer.hpp"
#include "pixl/src/core/vertex-array.hpp"
#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class Render {
public:
    Render(const std::string &vshader, const std::string &fshader);
    void render(const std::string &path, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

    VertexArray &getVAO() { return _VAO; }
    VertexBuffer &getVBO() { return _VBO; }
    VertexBuffer &getEBO() { return _EBO; }
private:
    void loadVertices(const std::string &path, float *vertices);

    Shader _shader;

    VertexArray _VAO;
    VertexBuffer _VBO;
    VertexBuffer _EBO;
};

} // namespace pixl

#endif // PIXL_RENDER_HPP
