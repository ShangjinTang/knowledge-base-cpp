#include "entity.h"

Entity::Entity(std::string name) : name(name) {
    std::cout << "Create entity" << std::endl;
}
Entity::~Entity() {
    std::cout << "Destroy entity" << std::endl;
}

void Entity::print_info() {
    std::cout << "Entity info: "
              << "name=" << name << std::endl;
}
