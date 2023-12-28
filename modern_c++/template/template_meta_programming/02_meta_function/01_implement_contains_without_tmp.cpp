#include <iostream>
#include <string_view>
#include <vector>

using std::tuple_element_t;

bool contains(std::string_view str_to_search, const std::vector<std::string_view>& vec, std::size_t start_index = 0) {
    if (vec[start_index] == str_to_search) {
        return true;
    }
    if (start_index == vec.size() - 1) {
        return false;
    }
    return contains(str_to_search, vec, start_index + 1);
}

int main() {
    std::vector<std::string_view> vec{"int", "bool", "float"};
    std::cout << std::boolalpha << contains("bool", vec) << std::endl;
    std::cout << std::boolalpha << contains("double", vec) << std::endl;

    return 0;
}
