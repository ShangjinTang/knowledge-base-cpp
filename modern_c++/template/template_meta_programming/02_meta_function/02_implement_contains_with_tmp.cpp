#include <iostream>
#include <tuple>
#include <type_traits>

using std::tuple_element_t;

template <bool condition, typename Then, typename Else>
struct If;

template <typename Then, typename Else>
struct If<true, Then, Else> {
    using Type = Then;
};

template <typename Then, typename Else>
struct If<false, Then, Else> {
    using Type = Else;
};

template <bool condition, typename Then, typename Else>
using IfT = typename If<condition, Then, Else>::Type;

// clang-format off
template <typename Search, typename Tuple, size_t start_index = 0>
struct ContainsType :
IfT <
    std::is_same_v<tuple_element_t<start_index, Tuple>, Search>,
    std::true_type,
    IfT <
        start_index == std::tuple_size_v<Tuple> - 1,
        std::false_type,
        ContainsType<Search, Tuple, start_index + 1>
    >
>
{};
// clang-format on

// partial specialization for empty tuple
template <typename Search>
struct ContainsType<Search, std::tuple<>, 0> : std::false_type {};

int main() {
    std::tuple<int, bool, float> type_tuple{};
    std::cout << std::boolalpha << ContainsType<bool, decltype(type_tuple)>::value << std::endl;
    std::cout << std::boolalpha << ContainsType<double, decltype(type_tuple)>::value << std::endl;

    std::tuple<> empty_tuple{};
    std::cout << std::boolalpha << ContainsType<double, decltype(empty_tuple)>::value << std::endl;
    return 0;
}
