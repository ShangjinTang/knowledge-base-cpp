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
    // Not allowed: create from raw pointer or "new"

    // Method 1: create by "std::weak_ptr" (empty)
    std::weak_ptr<Entity> p1_entity1;

    // Method 2: create by another weak pointer
    std::weak_ptr<Entity> p2_entity1(p1_entity1);

    // Method 3: create by another shared pointer
    std::shared_ptr<Entity> sp_entity2 = std::make_shared<Entity>("Emily");
    std::weak_ptr<Entity> p3_entity2(sp_entity2);

    return 0;
}
