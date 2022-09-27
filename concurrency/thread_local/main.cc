#include <iostream>
#include <mutex>
#include <thread>

#define N 3

std::mutex g_mutex;

// try to remove the "thread_local", run and check the differences
thread_local int g_val = 0;

int main() {
    std::cout << "main thread, address of g_val: " << &g_val << std::endl;
    auto func = [&](const std::string &name) {
        std::cout << "thread " << name << std::endl;
        std::cout << "thread: " << name << "  address of g_val: " << &g_val << std::endl;
        for (int i = 0; i < N; i++) {
            std::lock_guard guard(g_mutex);
            std::cout << "thread: " << name << ", g_val=" << g_val << std::endl;
            g_val++;
        }
    };
    std::thread t1(func, "t1");
    std::thread t2(func, "t2");
    t1.join();
    t2.join();
    std::cout << g_val << std::endl;
    return 0;
}
