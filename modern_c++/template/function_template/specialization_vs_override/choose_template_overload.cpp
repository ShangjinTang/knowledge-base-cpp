#include <fmt/printf.h>

template <typename T>
void print(T t) {
    fmt::println("Generic");
}

template <>
void print(double* t) {
    fmt::println("Specialization: double");
}

template <typename T>
void print(T* t) {
    fmt::println("Overload");
}

int main() {
    double i = 3.5;
    print(i);
    print(&i);
    return 0;
}
