#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

struct Div {
    void operator()(std::promise<int>&& intPromise, int a, int b) {
        try {
            if (b == 0) {
                std::string err_mess =
                        std::string("Illegal division by zero: ") + std::to_string(a) + "/" + std::to_string(b);
                throw std::runtime_error(err_mess);
            }
            intPromise.set_value(a / b);
        } catch (...) {
            intPromise.set_exception(std::current_exception());
        }
    }
};

void executeDivision(int nom, int denom) {
    std::promise<int> div_promise;
    std::future<int> div_result = div_promise.get_future();

    Div div;
    std::thread div_thread(div, std::move(div_promise), nom, denom);

    // get the result or the exception
    try {
        std::cout << nom << "/" << denom << " = " << div_result.get() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    div_thread.join();
}

int main() {
    std::cout << std::endl;

    executeDivision(20, 0);
    executeDivision(20, 10);

    std::cout << std::endl;
}
