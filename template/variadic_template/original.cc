#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

int main() {
    std::cout << to_string(42) << '\n';
    std::cout << to_string(5.3) << '\n';
    std::cout << to_string("Hello") << '\n';

    return 0;
}
