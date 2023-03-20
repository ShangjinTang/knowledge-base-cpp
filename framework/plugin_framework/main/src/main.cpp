#include <mutex>

#include "Loadable.h"
#include "LoadableFile.h"
#include "PluginManager.h"

#define LIB_DEFAULT_PATH "."
Loadable::PluginManager *plugin_manager;
std::recursive_mutex plugin_mutex;
extern "C" void load_plugins() {
    Loadable::PluginRegistry reg;

    reg.add("libhello.so", std::make_shared<Loadable::LoadableModule>("libhello.so", LIB_DEFAULT_PATH));
    std::lock_guard<std::recursive_mutex> lock(plugin_mutex);
    if (plugin_manager == nullptr) {
        plugin_manager = new Loadable::PluginManager(reg);
    }
    if (plugin_manager != nullptr) {
        plugin_manager->load();
        plugin_manager->init();
        plugin_manager->deinit();
        plugin_manager->unload();
    }
}

int main() {
    load_plugins();
    return 0;
}
