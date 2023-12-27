#include <iostream>
#include <type_traits>

template <typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

template <typename T>
void print1(T t) {
    if constexpr (is_pointer<T>::value) {
        std::cout << *t;
    } else {
        std::cout << t;
    }
}

template <typename T1, typename T2, typename T3>
void print3(T1 t1, T2 t2, T3 t3) {
    print1(t1);
    print1(" ");
    print1(t2);
    print1(" ");
    print1(t3);
    print1("\n");
}

int main() {
    std::string hello = "hello";
    std::string world = "world";
    constexpr int year = 2023;
    print3(&hello, world, year);
    return 0;
}
