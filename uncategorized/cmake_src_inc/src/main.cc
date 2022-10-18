#include <iostream>
#include <memory>

#include "entity.h"

int main() {
    std::shared_ptr<Entity> p1 = std::make_shared<Entity>("Cat");
    std::shared_ptr<Entity> p2 = p1;
    p2->print_info();
    return 0;
}
