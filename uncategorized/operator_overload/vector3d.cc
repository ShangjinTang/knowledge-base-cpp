#include "vector3d.h"

#include <iostream>
#include <ostream>

Vector3D::Vector3D(const float &x, const float &y, const float &z)
    : x(x), y(y), z(z) {
    /* std::cout << "Create Vector" << std::endl; */
}

Vector3D::~Vector3D() { /* std::cout << "Destroy Vector" << std::endl; */
}

Vector3D Vector3D::operator+(const Vector3D &other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

std::ostream &operator<<(std::ostream &out, const Vector3D &v) {
    out << "(" << v.x << "," << v.y << "," << v.z << ")";
    return out;
}
