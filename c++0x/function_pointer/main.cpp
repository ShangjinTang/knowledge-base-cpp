#include <iostream>
#include <vector>

typedef void (*Function)(int);

void PrintSquare(int t) { std::cout << t * t << std::endl; }

void ForEach(const std::vector<int> &values, Function function) {
    for (auto value : values) {
        function(value);
    }
}

int main() {
    std::vector<int> values = {1, 3, 4, 5, 2};
    ForEach(values, PrintSquare);
}
