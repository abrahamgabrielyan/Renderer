#include "Renderer.hpp"
#include "Logger.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

void Renderer::render(const Scene& scene, const std::array<float, 3>& color) {
    Logger& logger = Logger::getInstance();
    logger.logInfo("Renderer::render called with " + std::to_string(scene.meshes.size()) + " meshes");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
    GLint mode[2];
    glGetIntegerv(GL_POLYGON_MODE, mode);
    logger.logInfo("Polygon mode: " + std::to_string(mode[0]) + " (6914 = GL_FILL)");

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    // Light in world space
    GLfloat lightPos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    // Material with selected color
    GLfloat matDiffuse[] = {color[0], color[1], color[2], 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);

    // Camera setup
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 vp = proj * view;

    static float angle = 0.0f;
    angle += 0.01f;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));

    for (const auto& mesh : scene.meshes) {
        glBegin(GL_TRIANGLES);
        for (unsigned int idx : mesh->indices) {
            const Vertex& v = mesh->vertices[idx];
            glm::vec3 rotatedNormal = glm::mat3(rotation) * v.normal;
            glNormal3fv(&rotatedNormal[0]);
            glm::vec4 pos = vp * rotation * mesh->modelMatrix * glm::vec4(v.position, 1.0f);
            glVertex3f(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
        }
        glEnd();
    }

    glDisable(GL_LIGHTING);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        logger.logError("OpenGL error after rendering: " + std::to_string(err));
    }
}
