#include <iostream>
#include <memory>
#include <string>

class Entity {
public:
    Entity() = default;
    Entity(std::string name) : name(name) {
        std::cout << "Create entity" << std::endl;
    }
    ~Entity() {
        std::cout << "Destroy entity" << std::endl;
    }
    void print_info() const {
        std::cout << "Entity name=" << name << std::endl;
    }

private:
    std::string name{};
};

void print_by_pass_value(std::shared_ptr<Entity> p_entity) {
    std::cout << "p_entity.use_count(): " << p_entity.use_count() << std::endl;
    p_entity->print_info();
}

void print_by_pass_reference(std::shared_ptr<Entity> &p_entity) {
    std::cout << "p_entity.use_count(): " << p_entity.use_count() << std::endl;
    p_entity->print_info();
}

int main() {
    auto p_entity1 = std::make_shared<Entity>("Alice");
    std::cout << "p_entity1.use_count(): " << p_entity1.use_count() << std::endl;
    print_by_pass_value(p_entity1);
    std::cout << "p_entity1.use_count(): " << p_entity1.use_count() << std::endl;

    auto p_entity2 = std::make_shared<Entity>("Benjamin");
    std::cout << "p_entity2.use_count(): " << p_entity2.use_count() << std::endl;
    print_by_pass_reference(p_entity2);
    std::cout << "p_entity2.use_count(): " << p_entity2.use_count() << std::endl;

    return 0;
}
