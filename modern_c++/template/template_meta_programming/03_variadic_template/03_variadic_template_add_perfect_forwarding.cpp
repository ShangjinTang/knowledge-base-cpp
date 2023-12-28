#include <iostream>
#include <tuple>
#include <type_traits>

template <typename T>
void printn(T&& t) {
    std::cout << std::boolalpha << std::forward<T>(t) << std::endl;
}
// note: this must be placed after above template
// otherwise `printn(ts...)` finally ends with printn() and error occurs:
//   "candidate expects at least 1 argument, 0 provided"
template <typename T0, typename... Ts>
void printn(T0&& t0, Ts&&... ts) {
    std::cout << std::boolalpha << std::forward<T0>(t0) << ", ";
    printn(std::forward<Ts>(ts)...);
}

// for empty print
void printn() {
    std::cout << std::endl;
}

template <typename Tuple, std::size_t... indices>
void printTupleImpl(Tuple&& tuple, std::index_sequence<indices...> /*unused*/) {
    printn(std::get<indices>(std::forward<Tuple>(tuple))...);
}

template <typename Tuple>
void printTuple(Tuple&& tuple) {
    printTupleImpl(std::forward<Tuple>(tuple),
                   std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

int main() {
    auto my_tuple = std::make_tuple(42, "hello world", 0.1, true);
    printTuple(my_tuple);
    return 0;
}
