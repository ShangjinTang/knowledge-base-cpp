#include "libhello.h"

using hello::libhello;

int main() {
    libhello hello{};
    int32_t error_code = hello.saySomething("Hello Modern C++ Development");
    if (error_code > 0) {
        return error_code;
    }
#ifdef WITH_OPENSSL
    error_code = hello.saySomethingHashed("Hello Modern C++ Development");
    if (error_code > 0) {
        return error_code;
    }
#endif
    return 0;
}
