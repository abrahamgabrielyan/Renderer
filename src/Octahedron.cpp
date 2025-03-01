#include "Octahedron.hpp"

#include <glm/glm.hpp>

Octahedron::Octahedron(const float size) {
    float s = size / std::sqrt(2.0f);
    vertices = {
        {{ s,  0,  0}, {0.707f, 0, 0}, {0, 0}}, // 0: +X
        {{-s,  0,  0}, {-0.707f, 0, 0}, {1, 0}}, // 1: -X
        {{ 0,  s,  0}, {0, 0.707f, 0}, {0, 1}}, // 2: +Y
        {{ 0, -s,  0}, {0, -0.707f, 0}, {1, 1}}, // 3: -Y
        {{ 0,  0,  s}, {0, 0, 0.707f}, {0.5f, 0}}, // 4: +Z
        {{ 0,  0, -s}, {0, 0, -0.707f}, {0.5f, 1}}  // 5: -Z
    };

    indices = {
        0, 2, 4, // +X, +Y, +Z
        0, 4, 3, // +X, +Z, -Y
        0, 3, 5, // +X, -Y, -Z
        0, 5, 2, // +X, -Z, +Y
        1, 2, 5, // -X, +Y, -Z
        1, 5, 3, // -X, -Z, -Y
        1, 3, 4, // -X, -Y, +Z
        1, 4, 2  // -X, +Z, +Y
    };
}
