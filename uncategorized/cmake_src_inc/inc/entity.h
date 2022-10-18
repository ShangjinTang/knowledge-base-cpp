#pragma once
#include <iostream>
#include <string>

class Entity {
public:
    Entity() = default;
    Entity(std::string name);
    ~Entity();
    void print_info();

private:
    std::string name;
};
