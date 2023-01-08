#include <iostream>
#include <mutex>

class LockGuard {
public:
    explicit LockGuard(std::mutex& m) : mutex_(m) {
        mutex_.lock();
    }

    ~LockGuard() {
        mutex_.unlock();
    }

private:
    std::mutex& mutex_;
};

int main() {
    std::mutex m;
    LockGuard lock_guard(m);

    // Here, we can safely access our shared resource
    std::cout << "Accessing shared resource" << std::endl;

    // The lock_guard will be destroyed when it goes out of scope
    // at the end of this block, and the lock on the mutex will be released

    return 0;
}
