#include "Cylinder.hpp"

Cylinder::Cylinder(const float radius, const float height, const int32_t sectors) {
    const float halfHeight = height / 2.0f;
    const float angleStep = 2.0f * M_PI / sectors;

    vertices.push_back({{0, -halfHeight, 0}, {0, -1, 0}, {0.5f, 0.5f}}); // Bottom center
    vertices.push_back({{0, halfHeight, 0}, {0, 1, 0}, {0.5f, 0.5f}});   // Top center

    for (int32_t i = 0; i <= sectors; ++i) {
        const float angle = i * angleStep;
        const float x = radius * std::cos(angle);
        const float z = radius * std::sin(angle);
        vertices.push_back({{x, -halfHeight, z}, {0, -1, 0}, {0.5f + 0.5f * std::cos(angle), 
                                                              0.5f + 0.5f * std::sin(angle)}}); // Bottom edge
        vertices.push_back({{x, halfHeight, z}, {0, 1, 0}, {0.5f + 0.5f * std::cos(angle), 
                                                            0.5f + 0.5f * std::sin(angle)}});   // Top edge
        vertices.push_back({{x, halfHeight, z}, {std::cos(angle), 0, std::sin(angle)}, 
                                                {static_cast<float>(i) / sectors, 1.0f}}); // Side normal
        vertices.push_back({{x, -halfHeight, z}, {std::cos(angle), 0, std::sin(angle)}, 
                                                 {static_cast<float>(i) / sectors, 0.0f}}); // Side normal
    }

    // Bottom cap
    for (int32_t i = 0; i < sectors; ++i) {
        indices.push_back(0);           // Bottom center
        indices.push_back(2 + i * 4);   // Bottom edge i
        indices.push_back(2 + (i + 1) * 4 % (sectors * 4)); // Next bottom edge
    }

    // Top cap
    for (int32_t i = 0; i < sectors; ++i) {
        indices.push_back(1);           // Top center
        indices.push_back(3 + (i + 1) * 4 % (sectors * 4)); // Next top edge
        indices.push_back(3 + i * 4);   // Top edge i
    }

    // Sides
    for (int32_t i = 0; i < sectors; ++i) {
        const int32_t next = (i + 1) % sectors;
        indices.push_back(4 + i * 4);     // Side top i
        indices.push_back(5 + i * 4);     // Side bottom i
        indices.push_back(5 + next * 4);  // Side bottom next
        indices.push_back(4 + i * 4);     // Side top i
        indices.push_back(5 + next * 4);  // Side bottom next
        indices.push_back(4 + next * 4);  // Side top next
    }
}
