#include <iostream>
#include <mutex>
#include <thread>

std::once_flag once_flag;

void do_once() {
    std::call_once(once_flag, []() {
        std::cout << "This funtion is called only once." << std::endl;
    });
}

int main() {
    std::cout << std::endl;

    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once);
    std::thread t4(do_once);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << std::endl;
}
