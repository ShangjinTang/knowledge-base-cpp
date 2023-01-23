#include <iostream>
#include <list>
#include <vector>

// Variable template that checks if a type has begin() and end() member functions
template <typename T, typename = void>
struct is_iterable : std::false_type {};

// This gets used only when we can call std::begin() and std::end() on that type
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>>
        : std::true_type {};

// Variable template (since C++14)
template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

// Concepts (since C++20)
template <typename T>
concept Iterable = is_iterable_v<T>;

// Using concept in template (since C++20)
template <Iterable T>
void print_container(T t) {
    for (auto elem : t) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    using VectorInt = std::vector<int>;
    VectorInt vec_int{1, 2, 3, 4};
    print_container<VectorInt>(vec_int);

    using ListChar = std::list<char>;
    ListChar list_char{'a', 'b', 'c', 'd'};
    // Class template argument deduction (CTAD) (since C++17)
    print_container(list_char);

    return 0;
}
