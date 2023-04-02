#include <iostream>
#include <mutex>
#include <shared_mutex>

#include "Loadable.h"

class Module {
public:
    Module() = default;
    void init() {
        std::cout << "hello_module: hello world" << std::endl;
    };
    void deinit() {
        std::cout << "hello_module: goodbye" << std::endl;
    };
};

static struct LoadableHeader *theHeader = nullptr;
static std::shared_mutex theHeaderMutex;
extern "C" struct LoadableHeader *loadable_init() {
    std::unique_lock<std::shared_mutex> lock(theHeaderMutex);
    if (theHeader == nullptr) {
        auto hello_module = std::make_shared<Module>();
        if (hello_module) {
            hello_module->init();
        }
        auto header = new LoadableHeader{"HelloModule", hello_module};
        theHeader = header;
    }
    return theHeader;
}

extern "C" int loadable_deinit() {
    std::unique_lock<std::shared_mutex> lock(theHeaderMutex);
    if (theHeader != nullptr) {
        std::static_pointer_cast<Module>(theHeader->theModule)->deinit();
        delete theHeader;
    }
    return 0;
}
