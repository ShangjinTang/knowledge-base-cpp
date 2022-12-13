#include <iostream>
#include <thread>

class ThreadGuard {
public:
    explicit ThreadGuard(std::thread& t) : t_(t) {}
    ~ThreadGuard() {
        if (t_.joinable()) {
            t_.join();
        }
    }
    // disable copy constructor and copy assignment operator
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
    // enable move constructor and move assignment operator
    ThreadGuard(ThreadGuard&&) = default;
    ThreadGuard& operator=(ThreadGuard&&) = default;

private:
    std::thread& t_;
};

struct Func {
    explicit Func(int& i) : i_(i) {}
    void operator()() {
        for (unsigned int j = 0; j < 100000; ++j) {
            std::cout << j << std::endl;
        }
    }

private:
    int& i_;
};

int main() {
    int some_local_state = 0;
    Func my_func(some_local_state);
    std::thread my_thread(my_func);
    ThreadGuard thread_guard(my_thread);
}
