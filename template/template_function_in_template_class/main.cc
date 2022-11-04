#include <iostream>
#include <memory>

template <typename T>
class A {
public:
    template <typename U>
    U convert_type(T);
};

template <typename T>
template <typename U>
U A<T>::convert_type(T t) {
    return static_cast<U>(t);
}

int main() {
    double num_double = 4.5;
    std::unique_ptr<A<double>> pa = std::make_unique<A<double>>();
    auto num_int = pa->convert_type<int>(num_double);
    std::cout << num_int << std::endl;
    return 0;
}
