#include <future>
#include <iostream>
#include <thread>
#include <utility>

std::mutex cout_mutex;

struct Div {
    void operator()(std::promise<int>&& intPromise, int a, int b) {
        intPromise.set_value(a / b);
    }
};

struct Requestor {
    void operator()(const std::shared_future<int>& shared_fut) {
        // lock std::cout
        std::lock_guard<std::mutex> cout_guard(cout_mutex);

        // get the thread id
        std::cout << "threadId(" << std::this_thread::get_id() << "): ";

        std::cout << "20/10= " << shared_fut.get() << std::endl;
    }
};

int main() {
    std::cout << std::endl;

    // define the promises
    std::promise<int> div_promise;

    // get the futures
    std::shared_future<int> div_result = div_promise.get_future();

    // calculate the result in a separat thread
    Div div;
    std::thread div_thread(div, std::move(div_promise), 20, 10);

    Requestor req;
    std::thread shared_thread1(req, div_result);
    std::thread shared_thread2(req, div_result);
    std::thread shared_thread3(req, div_result);
    std::thread shared_thread4(req, div_result);
    std::thread shared_thread5(req, div_result);

    div_thread.join();

    shared_thread1.join();
    shared_thread2.join();
    shared_thread3.join();
    shared_thread4.join();
    shared_thread5.join();

    std::cout << std::endl;
}
