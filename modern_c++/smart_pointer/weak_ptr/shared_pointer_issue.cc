#include <iostream>
#include <memory>

class A;
class B;

class A {
public:
    ~A() {
        std::cout << "A destructor\n";
    }
    std::shared_ptr<B> ptr;
};

class B {
public:
    ~B() {
        std::cout << "B destructor\n";
    }
    std::shared_ptr<A> ptr;
};

int main() {
    {
        std::shared_ptr<A> aPtr = std::make_shared<A>();
        std::shared_ptr<B> bPtr = std::make_shared<B>();

        aPtr->ptr = bPtr;
        bPtr->ptr = aPtr;
    }

    std::cout << "program finished" << std::endl;

    return 0;
}
