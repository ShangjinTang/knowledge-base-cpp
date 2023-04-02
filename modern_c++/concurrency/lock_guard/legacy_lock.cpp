#include <mutex>

int main() {
    std::mutex m;
    m.lock();

    // Here, we can safely access our shared resource
    std::cout << "Accessing shared resource" << std::endl;

    // The lock_guard should be manually destroyed when it goes out of scope
    m.unlock();

    return 0;
}
