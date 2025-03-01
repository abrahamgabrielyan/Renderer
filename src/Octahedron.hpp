#ifndef OCTAHEDRON_HPP
#define OCTAHEDRON_HPP

#include "Mesh.hpp"

class Octahedron : public Mesh {
public:
    Octahedron(const float size = 1.0f);

    Octahedron(const Octahedron&);
    Octahedron(Octahedron&&);
    Octahedron& operator=(const Octahedron&);
    Octahedron& operator=(Octahedron&&);
};

#endif // OCTAHEDRON_HPP
