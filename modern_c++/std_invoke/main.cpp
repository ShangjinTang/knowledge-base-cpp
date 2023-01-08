#include <functional>
#include <iostream>

int do_something(const int i) {
    return 4 + i;
}

class S {
public:
    int j = 5;
    int do_something(const int i) {
        return j + i;
    }
};

int main() {
    /* std::cout << std::invoke(&do_something, 5) << std::endl; */

    S s;
    /* s.do_something(3); */
    /* std::cout << s.do_something(3) << std::endl; */
    std::cout << std::invoke(&S::do_something, s, 3) << std::endl;
    return 0;
}
