#include "pixl/src/core/model.hpp"
#include "pixl/include/glm/ext/vector_float3.hpp"
#include "pixl/src/core/mesh.hpp"

namespace pixl {

Model::Model(const std::string &path) {
    loadModel(path);
}

void Model::drawModel(Shader &shader) {
    for (auto &mesh: _meshes) {
        mesh.draw(shader);
    }
}

void Model::loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE) {
        std::cout << "Error::Assimp::" << importer.GetErrorString() << std::endl;
    } else {
        std::cout << "Success::Assimp::" << std::endl;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (uint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh));
    }

    for (uint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh) {
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    for (uint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex._position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex._normal = vector;

        vertices.push_back(vertex);
    }

    for (uint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);

}

} // namespace pixl
