#ifndef PIXL_SCENE_HPP
#define PIXL_SCENE_HPP

#include "pixl/src/core/model.hpp"

namespace pixl {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    std::vector<Model *> &getModels() { return _models; }
    void addModel(Model *model) { _models.push_back(model); }
private:
    std::vector<Model *> _models;
};

} // namespace pixl

#endif // PIXL_SCENE_HPP
