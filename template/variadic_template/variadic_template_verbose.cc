#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
std::string to_string_impl(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::vector<std::string> to_string() {
    return {};
}

template <typename Param1, typename... Params>
std::vector<std::string> to_string(const Param1& param1, const Params&... params) {
    std::vector<std::string> s;
    s.push_back(to_string_impl(param1));

    const auto remainder = to_string(params...);
    s.insert(s.end(), remainder.begin(), remainder.end());
    return s;
}

int main() {
    const auto vec = to_string("hello", 42, 5.3);

    for (const auto& o : vec) {
        std::cout << o << '\n';
    }

    return 0;
}
