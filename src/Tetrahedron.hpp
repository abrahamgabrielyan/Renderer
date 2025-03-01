#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "Mesh.hpp"

class Tetrahedron : public Mesh {
public:
    Tetrahedron(const float size = 1.0f);

    Tetrahedron(const Tetrahedron&);
    Tetrahedron(Tetrahedron&&);
    Tetrahedron& operator=(const Tetrahedron&);
    Tetrahedron& operator=(Tetrahedron&&);
};

#endif // TETRAHEDRON_HPP
