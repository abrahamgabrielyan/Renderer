#ifndef GUI_HPP
#define GUI_HPP

#include "Scene.hpp"
#include "Renderer.hpp"

#include <imgui.h>
#include <array>

class GUI {
public:
    GUI(Scene& scene, Renderer& renderer);
    void draw();
    std::array<float, 3> color;

    GUI(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI& operator=(GUI&&) = delete;

private:
    Scene& scene;
    Renderer& renderer;
};

#endif // GUI_HPP
