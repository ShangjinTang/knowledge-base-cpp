#include <iostream>
#include <mutex>

class MySingleton {
private:
    static std::once_flag init_instance_flag_;
    static MySingleton* instance_;
    MySingleton() = default;
    ~MySingleton() = default;

public:
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

    static MySingleton* getInstance() {
        call_once(init_instance_flag_, MySingleton::initSingleton);
        return instance_;
    }

    static void initSingleton() {
        instance_ = new MySingleton();
    }
};

MySingleton* MySingleton::instance_ = nullptr;
std::once_flag MySingleton::init_instance_flag_;

int main() {
    std::cout << "MySingleton::getInstance(): " << MySingleton::getInstance() << std::endl;
    std::cout << "MySingleton::getInstance(): " << MySingleton::getInstance() << std::endl;

    return 0;
}
