#ifndef PIXL_MODEL_HPP
#define PIXL_MODEL_HPP

#include "pixl/src/core/texture.hpp"
#include "pixl/src/pixl-precomp.hpp"
#include "pixl/src/core/mesh.hpp"

namespace pixl {

class Model {
public:
    Model(const std::string &path);
    void drawModel(Shader &shader);
private:
    std::vector<Mesh> _meshes;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture *> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType typeName); };

} // namespace pixl

#endif //PIXEL_MODEL_HPP
