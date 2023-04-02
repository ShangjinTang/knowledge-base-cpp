#include <mutex>

#include "Loadable.h"
#include "LoadableFile.h"
#include "PluginManager.h"

#define LIB_DEFAULT_PATH "."
#define LIB_HELLO "libhello.so"

int main() {
    std::unique_ptr<Loadable::PluginManager> plugin_manager;
    std::recursive_mutex plugin_mutex;
    Loadable::PluginRegistry reg;

    reg.add("libhello.so", std::make_shared<Loadable::LoadableModule>("libhello.so", LIB_DEFAULT_PATH));
    plugin_manager = std::make_unique<Loadable::PluginManager>(Loadable::PluginManager(reg));
    std::lock_guard<std::recursive_mutex> lock(plugin_mutex);
    if (plugin_manager == nullptr) {
        plugin_manager = std::make_unique<Loadable::PluginManager>(Loadable::PluginManager(reg));
    }
    if (plugin_manager != nullptr) {
        plugin_manager->load();
        plugin_manager->init();
        plugin_manager->deinit();
        plugin_manager->unload();
    }

    return 0;
}
