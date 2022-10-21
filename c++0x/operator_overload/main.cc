#include <iostream>

#include "vector3d.h"

int main() {
    Vector3D a_v3d = Vector3D(1, 2, 3);
    Vector3D b_v3d = Vector3D(4, 5, 6);
    std::cout << "a=" << a_v3d << std::endl;
    std::cout << "b=" << b_v3d << std::endl;

    Vector3D sum_v3d = b_v3d + a_v3d;
    std::cout << "b+a=" << sum_v3d << std::endl;
    Vector3D diff_v3d = b_v3d - a_v3d;
    std::cout << "b-a=" << diff_v3d << std::endl;
}
