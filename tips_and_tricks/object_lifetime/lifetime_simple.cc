#include <fmt/format.h>

struct Lifetime {
    Lifetime() noexcept {
        fmt::print("Lifetime() [default constructor]\n");
    }
    ~Lifetime() noexcept {
        fmt::print("~Lifetime() [destructor]\n");
    }
    Lifetime(const Lifetime &) noexcept {
        fmt::print("Lifetime(const Lifetime &) [copy constructor]\n");
    }
    Lifetime(Lifetime &&) noexcept {
        fmt::print("Lifetime(Lifetime &&) [move constructor]\n");
    }

    Lifetime &operator=(const Lifetime &other) noexcept {
        if (&other == this) {
            fmt::print("self assignment! ");
        }
        fmt::print("operator=(const Lifetime &) [copy assignment operator]\n");
        return *this;
    }
    Lifetime &operator=(Lifetime &&) noexcept {
        fmt::print("operator=(Lifetime &&) [move assignment operator]\n");
        return *this;
    }
};

int main() {
    fmt::print("Before lambda construction\n");
    auto lambda = [lft = Lifetime{}]() {

    };

    fmt::print("Before lambda call\n");
    lambda();
    fmt::print("After lambda call\n");
}
