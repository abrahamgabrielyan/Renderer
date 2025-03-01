#include "GUI.hpp"

#include "Cube.hpp"
#include "Tetrahedron.hpp"
#include "Octahedron.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Logger.hpp"
#include <fstream>

GUI::GUI(Scene& s, Renderer& r) : scene(s), renderer(r), color{1.0f, 0.0f, 0.0f} {
    Logger::getInstance().logInfo("GUI initialized");
}

void GUI::draw() {
    Logger::getInstance().logInfo("Drawing GUI");
    static int32_t selectedItem = 0;
    const char* items[] = {"None", "Tetrahedron", "Cube", "Octahedron",
                           "Sphere", "Cone", "Cylinder"};

    ImGui::Begin("Figure Selector");
    ImGui::Combo("Select Figure", &selectedItem, items, IM_ARRAYSIZE(items));
    float* color_data = color.data();
    ImGui::ColorEdit3("Object Color", color_data);

    if (ImGui::Button("Render")) {
        Logger& logger = Logger::getInstance();
        std::string name = items[selectedItem];
        logger.logInfo("Render button clicked with selection: " + name);

        scene.clear();
        logger.logInfo("Scene cleared");

        switch (selectedItem) {
            case 1: scene.addMesh(std::make_unique<Tetrahedron>(1.0f)); logger.logInfo("Creating tetrahedron"); break;
            case 2: scene.addMesh(std::make_unique<Cube>()); logger.logInfo("Creating cube"); break;
            case 3: scene.addMesh(std::make_unique<Octahedron>(1.0f)); logger.logInfo("Creating octahedron"); break;
            case 4: scene.addMesh(std::make_unique<Sphere>(1.0f, 36, 18)); logger.logInfo("Creating sphere"); break;
            case 5: scene.addMesh(std::make_unique<Cone>(1.0f, 2.0f, 36)); logger.logInfo("Creating cone"); break;
            case 6: scene.addMesh(std::make_unique<Cylinder>(1.0f, 2.0f, 36)); logger.logInfo("Creating cylinder"); break;
            default: logger.logWarning("No figure selected (None)"); break;
        }

        if (!scene.meshes.empty()) {
            logger.logInfo("Scene has " + std::to_string(scene.meshes.size()) + 
                           " meshes, rendering with color R:" +
                           std::to_string(color[0]) + " G:" + 
                           std::to_string(color[1]) + " B:" + std::to_string(color[2]));
            renderer.render(scene, color);
        } else {
            logger.logWarning("No meshes to render");
        }
    }

    if (ImGui::Button("Save")) {
        Logger& logger = Logger::getInstance();
        if (!scene.meshes.empty()) {
            std::string filename = std::string(items[selectedItem]) + ".obj";
            std::ofstream file(filename);
            if (file.is_open()) {
                const auto& mesh = scene.meshes[0];
                for (const auto& v : mesh->vertices) {
                    file << "v " << v.position.x << " " << v.position.y << " " << v.position.z << "\n";
                }
                for (std::size_t i = 0; i < mesh->indices.size(); i += 3) {
                    file << "f " << mesh->indices[i] + 1 << " " << mesh->indices[i + 1] + 1 << 
                    " " << mesh->indices[i + 2] + 1 << "\n";
                }
                file.close();
                logger.logInfo("Saved mesh to " + filename);
            } else {
                logger.logError("Failed to save mesh to " + filename);
            }
        } else {
            logger.logWarning("No mesh to save");
        }
    }

    ImGui::End();
}
