#include <iostream>

template <typename T>
void printn(T t) {
    std::cout << std::boolalpha << t << std::endl;
}

// note: this must be placed after above template
// otherwise `printn(ts...)` finally ends with printn() and error occurs:
//   "candidate expects at least 1 argument, 0 provided"
template <typename T0, typename... Ts>
void printn(T0 t0, Ts... ts) {
    std::cout << std::boolalpha << t0 << ", ";
    printn(ts...);
}

// for empty print
void printn() {
    std::cout << std::endl;
}

int main() {
    printn(42, "hello world", 0.1, true);
    printn();
    return 0;
}
