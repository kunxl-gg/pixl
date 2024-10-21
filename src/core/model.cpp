#include "pixl/src/core/model.hpp"
#include "pixl/include/glm/ext/vector_float3.hpp"
#include "pixl/src/core/mesh.hpp"
#include "pixl/src/core/texture.hpp"

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
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

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
        _meshes.emplace_back(processMesh(mesh, scene));
    }

    for (uint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Texture *> textures;

    // process vertices
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

    // process indices
    for (uint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture *> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::kDiffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    return Mesh(vertices, indices, textures);
}

std::vector<Texture *> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureType typeName) {
    std::vector<Texture *> textures;
    for (uint i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);

        const char *path = str.C_Str();
        char directory[100] = "assets/backpack/";
        strcat(directory, path);
        const std::string filePath = directory;
        printf("Texture Path: %s\n", filePath.c_str());

        Texture *tex =  new Texture(filePath, typeName);
        textures.push_back(tex);
    }
    return textures;
}

} // namespace pixl
