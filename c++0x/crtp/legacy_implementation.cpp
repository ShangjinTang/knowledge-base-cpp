#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() = 0;
};

class Square : public Shape {
public:
    Square() = default;
    void draw() final {
        std::cout << "draw a square\n";
    }
};

class Rectangle : public Shape {
public:
    Rectangle() = default;
    void draw() final {
        std::cout << "draw a rectangle\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Rectangle>());

    for (const auto &shape : shapes) {
        shape->draw();
    }

    return 0;
}
