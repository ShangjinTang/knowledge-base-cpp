#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mu;
std::condition_variable cv;

bool data_ready{false};

void do_work() {
    std::cout << "Processing shared data." << std::endl;
}

void waiting_for_work() {
    std::cout << "Worker: Waiting for work." << std::endl;
    std::unique_lock<std::mutex> lk(mu);
    cv.wait(lk, [] {
        return data_ready;
    });
    do_work();
    std::cout << "Work done." << std::endl;
}

void set_data_ready() {
    {
        std::lock_guard<std::mutex> lk(mu);
        data_ready = true;
    }
    std::cout << "Sender: Data is ready." << std::endl;
    cv.notify_one();
}

int main() {
    std::thread t1(waiting_for_work);
    std::thread t2(set_data_ready);

    t1.join();
    t2.join();

    return 0;
}
