#include <iostream>
#include <type_traits>

template <typename T>
struct IsPointer {
    static constexpr bool VALUE = false;
};

template <typename T>
struct IsPointer<T*> {
    static constexpr bool VALUE = true;
};

template <typename T>
struct StripPointer {
    using Type = T;
};

template <typename T>
struct StripPointer<T*> {
    using Type = T;
};

template <typename T>
void print1(T t) {
    using RemovePointerType = typename StripPointer<T>::Type;
    if constexpr (IsPointer<T>::VALUE && std::is_integral_v<RemovePointerType>) {
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
    std::string hello_world = "hello world";
    constexpr int YEAR = 2023;
    constexpr int MONTH = 12;
    print3(&hello_world, &YEAR, &MONTH);
    return 0;
}
