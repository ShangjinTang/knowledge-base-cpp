#include <iostream>
#include <string>

template <typename T>
class Maybe;

template <typename T>
Maybe<T> maybe(T* ctx) {
    return Maybe<T>(ctx);
}

template <typename T>
class Maybe {
private:
    T* ctx;

public:
    explicit Maybe(T* const ctx) : ctx{ctx} {}

    template <typename Func>
    auto With(Func evaluator) {
        if (ctx != nullptr) {
            return maybe(evaluator(ctx));
        }
        return Maybe<typename std::remove_pointer<decltype(evaluator(ctx))>::type>(nullptr);
    }

    template <typename Func>
    auto Do(Func action) {
        if (ctx != nullptr) {
            action(ctx);
        }
        return *this;
    }
};

struct Address {
    std::string* house_name = nullptr;
};

struct Person {
    Address* address = nullptr;
};

void print_house_name(Person* p) {
    // if (p != nullptr && p->address != nullptr && p->address->house_name != nullptr) {
    //     std::cout << *p->address->house_name << std::endl;
    // }
    maybe(p).With([](auto x) {
                return x->address;
            })
            .With([](auto x) {
                return x->house_name;
            })
            .Do([](auto x) {
                std::cout << x << std::endl;
            });
}

int main(int /*argc*/, char* /*argv*/[]) {
    Person p;
    print_house_name(&p);
    std::cout << "end of main" << std::endl;
    return 0;
}
