#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "Loadable.h"

namespace Loadable {

class PluginRegistry {
private:
    using EntryType = std::tuple<std::string, bool, size_t, std::shared_ptr<LoadableModule>>;
    std::multimap<size_t, EntryType> modules;

public:
    void add(std::string name, std::shared_ptr<LoadableModule> module);
    void add(std::string name, std::shared_ptr<LoadableModule> module, bool mandatory, size_t prio);
    using foreachcb = std::function<void(std::string, std::shared_ptr<LoadableModule>, bool, size_t)>;
    void foreach (foreachcb cb);
};

PluginRegistry &getGlobalPluginRegistry();

class PluginManager {
private:
    PluginRegistry registry;

public:
    PluginManager(const PluginRegistry &registry);
    void load();
    int init();
    int deinit();
    void unload();
};

}  // namespace Loadable
