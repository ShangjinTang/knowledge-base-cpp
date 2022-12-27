#include <iostream>

class MySingleton {
public:
    static MySingleton& getInstance() {
        static MySingleton instance;
        return instance;
    }
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

private:
    MySingleton() = default;
    ~MySingleton() = default;
};

int main() {
    std::cout << "MySingleton::getInstance(): " << &MySingleton::getInstance() << std::endl;
    std::cout << "MySingleton::getInstance(): " << &MySingleton::getInstance() << std::endl;

    return 0;
}
