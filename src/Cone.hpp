#ifndef CONE_HPP
#define CONE_HPP

#include "Mesh.hpp"

#include <cmath>

class Cone : public Mesh {
public:
    Cone(const float radius = 1.0f, 
         const float height = 2.0f, 
         const int32_t sectors = 36);

    Cone(const Cone&) = delete;
    Cone(Cone&&) = delete;
    Cone& operator=(const Cone&) = delete;
    Cone& operator=(Cone&&) = delete;
};

#endif // CONE_HPP
