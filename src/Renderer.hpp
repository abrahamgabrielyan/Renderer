#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene.hpp"
#include "Logger.hpp"

#include <array>

class Renderer {
public:
    Renderer() = default;

    void render(const Scene& scene, const std::array<float, 3>& color);

    Renderer(const Renderer&);
    Renderer(Renderer&&);
    Renderer& operator=(const Renderer&);
    Renderer& operator=(Renderer&&);
};

#endif // RENDERER_HPP
