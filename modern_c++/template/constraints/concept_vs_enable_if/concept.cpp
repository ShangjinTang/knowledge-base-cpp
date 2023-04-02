#include <concepts>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

// Concepts (since C++20)
template <typename T>
concept Printable = requires(T t) {
                        { std::cout << t } -> std::same_as<std::ostream&>;
                    };
template <typename Container>
concept PrintableContainer = requires(Container c) {
                                 { c.begin() } -> std::convertible_to<typename Container::iterator>;
                                 { c.end() } -> std::convertible_to<typename Container::iterator>;
                                 requires Printable<typename Container::value_type>;
                             };

// Using requires with concept in template (since C++20)
template <typename T>
    requires PrintableContainer<T> && std::copyable<T>
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

    using VectorPairs = std::vector<std::pair<char, int>>;
    VectorPairs vector_pairs{{'a', 1}, {'b', 2}};
    // Line below would compile error because element std::pair is not printable, with user-friendly error message
    // print_container(vector_pairs);

    return 0;
}
