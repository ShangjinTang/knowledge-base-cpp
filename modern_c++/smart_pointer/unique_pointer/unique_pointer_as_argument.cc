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

void print_by_pass_value(std::unique_ptr<Entity> p_entity) {
    p_entity->print_info();
}

void print_by_pass_reference(std::unique_ptr<Entity> &p_entity) {
    p_entity->print_info();
}

int main() {
    auto p_entity1 = std::make_unique<Entity>("Alice");
    /* print_by_pass_value(p_entity1); */
    /* p_entity1->print_info(); */
    print_by_pass_value(std::move(p_entity1));
    std::cout << "address of p_entity1: " << p_entity1.get() << std::endl;

    auto p_entity2 = std::make_unique<Entity>("Benjamin");
    print_by_pass_reference(p_entity2);
    std::cout << "address of p_entity2: " << p_entity2.get() << std::endl;

    return 0;
}
