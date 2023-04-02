#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

int main() {
    auto func_add = std::make_shared<std::function<int(int, int)>>([](int a, int b) {
        return a + b;
    });

    std::packaged_task<int(int, int)> task1(*func_add);
    std::packaged_task<int(int, int)> task2(*func_add);

    std::future<int> result1 = task1.get_future();
    std::future<int> result2 = task2.get_future();

    std::thread t1(std::move(task1), 1, 2);
    std::thread t2(std::move(task2), 3, 5);

    t1.join();
    t2.join();

    std::cout << "Result1: " << result1.get() << std::endl;
    std::cout << "Result2: " << result2.get() << std::endl;

    return 0;
}
