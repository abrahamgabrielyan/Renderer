#include "Cone.hpp"

Cone::Cone(const float radius, const float height, const int32_t sectors) {
    const float angleStep = 2.0f * M_PI / sectors;

    vertices.push_back({{0, -height / 2, 0}, {0, -1, 0}, {0.5f, 0.5f}});
    vertices.push_back({{0, height / 2, 0}, {0, 1, 0}, {0.5f, 0.5f}});

    for (int32_t i = 0; i <= sectors; ++i) {
        const float angle = i * angleStep;
        const float x = radius * std::cos(angle);
        const float z = radius * std::sin(angle);
        vertices.push_back({{x, -height / 2, z}, {0, -1, 0}, {0.5f + 0.5f * std::cos(angle), 
                                                              0.5f + 0.5f * std::sin(angle)}});
        glm::vec3 normal = glm::normalize(glm::vec3(x, height / 2, z) - glm::vec3(0, height / 2, 0));
        vertices.push_back({{x, -height / 2, z}, normal, {static_cast<float>(i) / sectors, 0.0f}});
    }

    // Base
    for (int32_t i = 0; i < sectors; ++i) {
        indices.push_back(0);           // Bottom center
        indices.push_back(2 + i * 2);   // Base edge i
        indices.push_back(2 + (i + 1) * 2 % (sectors * 2)); // Next base edge
    }

    // Sides
    for (int32_t i = 0; i < sectors; ++i) {
        indices.push_back(1);           // Apex
        indices.push_back(3 + i * 2);   // Side base i
        indices.push_back(3 + (i + 1) * 2 % (sectors * 2)); // Next side base
    }
}
