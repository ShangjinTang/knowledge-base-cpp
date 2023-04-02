#include "PluginManager.h"

namespace Loadable {

void PluginRegistry::add(std::string name, std::shared_ptr<LoadableModule> module) {
    modules.insert({0, {name, false, 0, module}});
}

void PluginRegistry::add(std::string name, std::shared_ptr<LoadableModule> module, bool mandatory, size_t prio) {
    modules.insert({prio, {name, mandatory, prio, module}});
}

PluginManager::PluginManager(const PluginRegistry &registry) : registry(registry) {}

void PluginRegistry::foreach (PluginRegistry::foreachcb cb) {
    for (auto entry : modules) {
        auto &&[name, mandatory, priority, module] = entry.second;
        cb(name, module, mandatory, priority);
    }
}

void PluginManager::load() {
    printf("Loading plugins...\n");
    registry.foreach ([](std::string name, std::shared_ptr<LoadableModule> module, bool mandatory, size_t /* prio */) {
        if (module && !module->isLoaded()) {
            const char *cname = name.c_str();
            printf("Loading %s module %s\n", mandatory ? "mandatory" : "optional", cname);

            auto hndl = module->load();
            if (hndl == nullptr && mandatory) {
                printf("Unable to load mandatory module %s\n", cname);
                abort();
            }
            printf("%s module %s %sloaded\n", mandatory ? "Mandatory" : "Optional", cname,
                   (hndl == nullptr) ? "not " : "");
        }
    });
}

int PluginManager::init() {
    registry.foreach (
            [](std::string /* name */, std::shared_ptr<LoadableModule> module, bool /*mandatory*/, size_t /*prio*/) {
                if (module && module->isLoaded()) {
                    module->init();
                }
            });

    return 0;
}

int PluginManager::deinit() {
    registry.foreach (
            [](std::string /*name*/, std::shared_ptr<LoadableModule> module, bool /*mandatory*/, size_t /*prio*/) {
                if (module && module->isLoaded()) {
                    module->deinit();
                }
            });
    return 0;
}

void PluginManager::unload() {
    registry.foreach (
            [](std::string /*name*/, std::shared_ptr<LoadableModule> module, bool /*mandatory*/, size_t /*prio*/) {
                if (module && module->isLoaded()) {
                    module->unload();
                }
            });
}

}  // namespace Loadable
