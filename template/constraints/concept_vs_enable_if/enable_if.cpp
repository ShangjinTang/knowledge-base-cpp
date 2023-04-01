#include <concepts>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

// C++17 implementation
// Variable template that checks if a type has begin() and end() member functions
template <typename T, typename = void>
struct is_iterable : std::false_type {};

// std::void_t requires C++17
// This gets used only when we can call std::begin() and std::end() on that type
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>>
        : std::true_type {};

// Variable template (since C++14)
template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template <typename T, typename = std::enable_if_t<is_iterable_v<T>>>
void print_container(T t) {
    // can also use 'if constexpr (is_iterable_v<T>)' to replace enable_if in template declaration
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

    using VectorPairs = std::vector<std::pair<char, int>>;
    VectorPairs vector_pairs{{'a', 1}, {'b', 2}};
    // Line below would compile error because element std::pair is not printable, but the error message is hard to read
    // print_container(vector_pairs);

    return 0;
}
