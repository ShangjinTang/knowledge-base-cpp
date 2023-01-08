#include <functional>
#include <iostream>

int fetch_square(const int i) {
    return i * i;
}

int main() {
    // standard function call
    std::cout << fetch_square(5) << std::endl;
    // call with std::invoke
    std::cout << std::invoke(&fetch_square, 5) << std::endl;

    return 0;
}
