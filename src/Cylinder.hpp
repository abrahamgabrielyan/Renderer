#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Mesh.hpp"

#include <cmath>

class Cylinder : public Mesh {
public:
    Cylinder(const float radius = 1.0f, 
             const float height = 2.0f, 
             const int32_t sectors = 36);

    Cylinder(const Cylinder&) = delete;
    Cylinder(Cylinder&&) = delete;
    Cylinder& operator=(const Cylinder&) = delete;
    Cylinder& operator=(Cylinder&&) = delete;
};

#endif // CYLINDER_HPP
