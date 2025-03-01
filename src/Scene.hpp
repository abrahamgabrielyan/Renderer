#ifndef SCENE_HPP
#define SCENE_HPP

#include "Mesh.hpp"
#include <vector>
#include <memory>

class Scene {
public:
    Scene() = default;

    std::vector<std::unique_ptr<Mesh>> meshes;
    void clear() { meshes.clear(); }
    void addMesh(std::unique_ptr<Mesh> mesh) { meshes.push_back(std::move(mesh)); }

    Scene(const Scene&);
    Scene(Scene&&);
    Scene& operator=(const Scene&);
    Scene& operator=(Scene&&);
};

#endif // SCENE_HPP
