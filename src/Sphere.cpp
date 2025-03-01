#include "Sphere.hpp"

#include <cmath>

Sphere::Sphere(const float radius, const int32_t sectors, const int32_t stacks) {
    float const R = 1.0f / (stacks - 1);
    float const S = 1.0f / (sectors - 1);

    vertices.resize(stacks * sectors);
    indices.resize((stacks - 1) * (sectors - 1) * 6);

    auto v = vertices.begin();
    for (int32_t r = 0; r < stacks; ++r) {
        for (int32_t s = 0; s < sectors; ++s) {
            float const y = std::sin(-M_PI_2 + M_PI * r * R);
            float const x = std::cos(2 * M_PI * s * S) * std::sin(M_PI * r * R);
            float const z = std::sin(2 * M_PI * s * S) * std::sin(M_PI * r * R);
            v->position = glm::vec3(x, y, z) * radius;
            v->normal = glm::normalize(v->position);
            v->texCoord = glm::vec2(s * S, r * R);
            ++v;
        }
    }

    auto i = indices.begin();
    for (int32_t r = 0; r < stacks - 1; ++r) {
        for (int32_t s = 0; s < sectors - 1; ++s) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = r * sectors + s;
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
        }
    }
}
