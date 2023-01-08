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

int main() {
    // Method 1: create from unique pointer (never use this)
    Entity *rp_entity1 = new Entity("Alice");
    std::unique_ptr<Entity> p_entity1(rp_entity1);
    rp_entity1 = nullptr;
    p_entity1->print_info();
    /* delete rp_entity1; */

    // Method 2: create from "new" (exception unsafe)
    std::unique_ptr<Entity> p_entity2(new Entity("Benjamin"));
    p_entity2->print_info();

    // Method 3: create by "std::make_unique"
    std::unique_ptr<Entity> p_entity3 = std::make_unique<Entity>("Chris");
    p_entity3->print_info();

    // Method 4: create by "std::make_unique" with declaration "auto"
    auto p_entity4 = std::make_unique<Entity>("Daniel");
    p_entity4->print_info();

    return 0;
}
