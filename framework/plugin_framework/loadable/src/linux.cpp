#include <dlfcn.h>
#include <unistd.h>

#include "Loadable.h"

void *loadLibrary(const std::string &libname) {
    void *fwhandle = dlopen(libname.c_str(), RTLD_NOW | RTLD_GLOBAL);
    return fwhandle;
}

using namespace Loadable;

/* Platform specific */
bool SearchPath::fileAccessible(std::string path, std::string filename) {
    bool ret = false;
    if (path.size() == 0) {
        path = ".";
    }
    std::string fullpath = path + "/" + filename;
    int res = access(fullpath.c_str(), R_OK);
    if (res == 0) {
        ret = true;
    }
    return ret;
}

void *ModuleHandle::findSymbol(std::string symname) {
    void *sym = dlsym(handle, symname.c_str());
    return sym;
}

ModuleHandle::ModuleHandle(std::string path) {
    handle = loadLibrary(path);
}

ModuleHandle::~ModuleHandle() {
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}
/* End platform specific */
