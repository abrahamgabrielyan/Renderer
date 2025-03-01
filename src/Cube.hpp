#ifndef CUBE_HPP
#define CUBE_HPP

#include "Mesh.hpp"

class Cube : public Mesh {
public:
    Cube();

    Cube(const Cube&) = delete;
    Cube(Cube&&) = delete;
    Cube& operator=(const Cube&) = delete;
    Cube& operator=(Cube&&) = delete;
};

#endif // CUBE_HPP
