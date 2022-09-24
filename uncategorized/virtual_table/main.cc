#include <iostream>

using p_function = void (*)();

class Base {
  public:
    virtual void a() { std::cout << "Base a()" << std::endl; }
    virtual void b() { std::cout << "Base b()" << std::endl; }
    virtual void c() { std::cout << "Base c()" << std::endl; }
};

class Derive : public Base {
  public:
    virtual void b() { std::cout << "Derive b()" << std::endl; }
};

int main() {
    Base *p_base = new Base;
    long *tmp_base = reinterpret_cast<long *>(p_base);
    long *vptr_base = (long *)(*tmp_base);
    for (int i = 0; i < 3; i++) {
        std::cout << "vptr_base: " << i << " - " << vptr_base[i] << std::endl;
        ((p_function)vptr_base[i])();
    }

    std::cout << std::endl;

    Derive *p_derive = new Derive;
    long *tmp_derive = reinterpret_cast<long *>(p_derive);
    long *vptr_derive = (long *)(*tmp_derive);
    for (int i = 0; i < 3; i++) {
        std::cout << "vptr_derive: " << i << " - " << vptr_derive[i] << std::endl;
        ((p_function)vptr_derive[i])();
    }

    return 0;
}
