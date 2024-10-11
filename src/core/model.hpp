#ifndef PIXL_MODEL_HPP
#define PIXL_MODEL_HPP

#include "pixl/src/pixl-precomp.hpp"
#include "pixl/src/core/mesh.hpp"

#include "pixl/include/assimp/types.h"
namespace pixl {

class Model {
public:
    Model(const std::string &path);
    void drawModel(Shader &shader);
private:
    std::vector<Mesh> _meshes;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh);
};

} // namespace pixl

#endif //PIXEL_MODEL_HPP
