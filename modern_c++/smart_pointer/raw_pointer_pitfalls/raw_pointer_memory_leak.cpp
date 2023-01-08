#include <iostream>

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

int main() {
    Entity *p_entity = new Entity("Alice");
    p_entity->print_info();

    return 0;
}
