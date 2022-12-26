#include <atomic>
#include <iostream>
#include <thread>

class SpinLock {
private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
    SpinLock() : flag_() {}
    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {
        }
    }
    void unlock() {
        flag_.clear(std::memory_order_release);
    }
};

SpinLock spin;

void work_on_resource() {
    spin.lock();
    // shared resource
    std::cout << "Doing some work" << std::endl;
    spin.unlock();
    std::cout << "Work done" << std::endl;
}

int main() {
    std::thread t1(work_on_resource);
    std::thread t2(work_on_resource);

    t1.join();
    t2.join();

    return 0;
}
