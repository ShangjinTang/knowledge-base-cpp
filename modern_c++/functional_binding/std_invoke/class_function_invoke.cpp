#include <functional>
#include <iostream>

class Calculator {
public:
    Calculator() = default;
    Calculator(int pow_count) : pow_count(pow_count) {}
    int fetch_pow(const int num) {
        int result = 1;
        for (int i = 0; i < pow_count; i++) {
            result *= num;
        }
        return result;
    }

private:
    int pow_count{2};
};

int main() {
    Calculator calculator;
    // standard function call
    std::cout << calculator.fetch_pow(4) << std::endl;
    // call with std::invoke
    std::cout << std::invoke(&Calculator::fetch_pow, calculator, 4) << std::endl;

    return 0;
}
