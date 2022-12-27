#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct CriticalData {
    std::mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b) {
    std::unique_lock<std::mutex> unique_guard_a(a.mut, std::adopt_lock);
    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::unique_lock<std::mutex> unique_guard_b(b.mut, std::adopt_lock);
    std::cout << "get the second mutex" << std::endl;
    std::lock(a.mut, b.mut);
    // do something with a and b
}

int main() {
    CriticalData c1;
    CriticalData c2;

    std::thread t1([&] {
        deadLock(c1, c2);
    });
    std::thread t2([&] {
        deadLock(c2, c1);
    });

    t1.join();
    t2.join();
}
