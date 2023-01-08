#include <iostream>

#include "function.h"

int f(int x, int y) {
    return x + y;
}

int main() {
    Function<int(int, int)> func_add{f};
    Function<int(int, int)> func_multiply{[](int x, int y) {
        return x * y;
    }};
    std::cout << "func_add(1, 2) + func_multiply(3, 4) = " << func_add(1, 2) + func_multiply(3, 4) << std::endl;
    return 0;
}
