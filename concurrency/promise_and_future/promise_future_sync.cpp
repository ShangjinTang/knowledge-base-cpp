#include <future>
#include <iostream>
#include <utility>

void do_work() {
    std::cout << "Processing shared data." << std::endl;
}

void waiting_for_work(std::future<void>&& fut) {
    std::cout << "Worker: Waiting for work." << std::endl;
    fut.wait();
    do_work();
    std::cout << "Work done." << std::endl;
}

void set_data_ready(std::promise<void>&& prom) {
    std::cout << "Sender: Data is ready." << std::endl;
    prom.set_value();
}

int main() {
    std::cout << std::endl;

    std::promise<void> send_ready;
    auto fut = send_ready.get_future();

    std::thread t1(waiting_for_work, std::move(fut));
    std::thread t2(set_data_ready, std::move(send_ready));

    t1.join();
    t2.join();

    std::cout << std::endl;
}
