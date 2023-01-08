#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

template <typename... Params>
std::vector<std::string> to_string(const Params&... params) {
    std::vector<std::string> s;

    auto to_string_impl = [](const auto& t) {
        std::stringstream ss;
        ss << t;
        return ss.str();
    };

    (s.emplace_back(to_string_impl(params)), ...);
    return s;
}

int main() {
    const auto vec = to_string("hello", 42, 5.3);

    for (const auto& o : vec) {
        std::cout << o << '\n';
    }

    return 0;
}
