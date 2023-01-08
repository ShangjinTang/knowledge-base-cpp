#include <iostream>
#include <thread>

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
    my_thread.detach();
}
