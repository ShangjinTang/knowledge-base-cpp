#include <algorithm>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

template <typename... Base>
struct Visitor : Base... {
    template <typename... T>
    Visitor(T &&...t) : Base(std::forward<T>(t))... {}
};

template <typename... T>
Visitor(T...) -> Visitor<std::decay_t<T>...>;

int main() {
    std::vector<std::variant<double, int, std::string>> a{3.2, 2, 3, 5, 2.9, "Hello world"};

    int int_sum = 0;
    double double_sum = 0;

    Visitor visitor{[&int_sum](const int i) {
                        int_sum += i;
                    },
                    [&double_sum](const double d) {
                        double_sum += d;
                    },
                    [](const std::string &s) {}};

    std::for_each(std::begin(a), std::end(a), [&visitor](const auto &value) {
        std::visit(visitor, value);
    });

    std::cout << "int_sum: " << int_sum << std::endl;
    std::cout << "double_sum: " << double_sum << std::endl;
    return 0;
}
