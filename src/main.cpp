#include "Scene.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"
#include "Logger.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
    Logger& logger = Logger::getInstance();
    logger.logInfo("Starting application");

    if (!glfwInit()) {
        logger.logError("Failed to initialize GLFW");
        const char* description = nullptr;
        const int32_t code = glfwGetError(&description);
        logger.logError("GLFW error code: " + std::to_string(code) + 
                        ", Description: " + (description ? description : "none"));
        return -1;
    }
    logger.logInfo("GLFW initialized");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Software Renderer", nullptr, nullptr);
    if (!window) {
        logger.logError("Failed to create GLFW window");
        const char* description = nullptr;
        const int32_t code = glfwGetError(&description);
        logger.logError("GLFW error code: " + std::to_string(code) + 
                        ", Description: " + (description ? description : "none"));
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    logger.logInfo("Window created");
    logger.logInfo("OpenGL version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        logger.logError("Failed to initialize ImGui GLFW backend");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 120")) {
        logger.logError("Failed to initialize ImGui OpenGL3 backend");
        ImGui_ImplGlfw_Shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    logger.logInfo("ImGui initialized");

    Scene scene;
    Renderer renderer;
    GUI gui(scene, renderer);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        gui.draw();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (!scene.meshes.empty()) {
            renderer.render(scene, gui.color);
        } else {
            logger.logInfo("No meshes in scene");
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    logger.logInfo("Shutting down");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
