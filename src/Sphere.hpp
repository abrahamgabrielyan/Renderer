#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Mesh.hpp"

class Sphere : public Mesh {
public:
    Sphere(const float radius = 1.0f, 
           const int sectors = 36, 
           const int32_t stacks = 18);

    Sphere(const Sphere&);
    Sphere(Sphere&&);
    Sphere& operator=(const Sphere&);
    Sphere& operator=(Sphere&&);
};

#endif // SPHERE_HPP
