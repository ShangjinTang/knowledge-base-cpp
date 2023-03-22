#include <dlfcn.h>

#include <iostream>

int main() {
    // 'RTLD_LAZY' must be used here: symbol 'logging' is extern and not resolved
    void* math_handle = dlopen("./libmath.so", RTLD_LAZY | RTLD_GLOBAL);
    if (math_handle == nullptr) {
        std::cerr << "Failed to load libfoo.so: " << dlerror() << std::endl;
        return 1;
    }
    std::cout << "Loaded libfoo.so" << std::endl;

    // 'RTLD_GLOBAL' must be used here: libmath.so depends on logging.so
    void* logging_handle = dlopen("./liblogging.so", RTLD_NOW | RTLD_GLOBAL);
    if (logging_handle == nullptr) {
        std::cerr << "Failed to load liblogging.so: " << dlerror() << std::endl;
        return 1;
    }
    std::cout << "Loaded liblogging.so" << std::endl;

    using func_t = int (*)(int, int);
    auto func_add = (func_t)(dlsym(math_handle, "add"));
    if (func_add == nullptr) {
        std::cerr << "Failed to find add() function in libfoo.so: " << dlerror() << std::endl;
        return 1;
    }
    std::cout << "func_add(2, 3):\n" << func_add(2, 3) << std::endl;

    dlclose(math_handle);

    return 0;
}
