#include "Tetrahedron.hpp"

#include <glm/glm.hpp>

Tetrahedron::Tetrahedron(const float size) {
    const float s = size / std::sqrt(2.0f);
    vertices = {
        {{ s,  s,  s}, {0.577f, 0.577f, 0.577f}, {0, 0}},   // 0
        {{ s, -s, -s}, {0.577f, -0.577f, -0.577f}, {1, 0}}, // 1
        {{-s,  s, -s}, {-0.577f, 0.577f, -0.577f}, {0, 1}}, // 2
        {{-s, -s,  s}, {-0.577f, -0.577f, 0.577f}, {1, 1}}  // 3
    };

    indices = {
        0, 1, 2, // Face 1
        0, 2, 3, // Face 2
        0, 3, 1, // Face 3
        1, 3, 2  // Face 4
    };
}
