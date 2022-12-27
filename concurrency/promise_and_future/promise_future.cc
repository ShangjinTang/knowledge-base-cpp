#include <future>
#include <iostream>
#include <thread>
#include <utility>

void product(std::promise<int>&& intPromise, int a, int b) {
    intPromise.set_value(a * b);
}

struct Div {
    void operator()(std::promise<int>&& intPromise, int a, int b) const {
        intPromise.set_value(a / b);
    }
};

int main() {
    int a = 20;
    int b = 10;

    std::cout << std::endl;

    // define the promises
    std::promise<int> prod_promise;
    std::promise<int> div_promise;

    // get the futures
    std::future<int> prod_result = prod_promise.get_future();
    std::future<int> div_result = div_promise.get_future();

    // calculate the result in a separate thread
    std::thread prod_thread(product, std::move(prod_promise), a, b);
    Div div;
    std::thread div_thread(div, std::move(div_promise), a, b);

    // get the result
    std::cout << "20*10 = " << prod_result.get() << std::endl;
    std::cout << "20/10 = " << div_result.get() << std::endl;

    prod_thread.join();

    div_thread.join();

    std::cout << std::endl;
}
