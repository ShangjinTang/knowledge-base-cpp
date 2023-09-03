#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() = 0;
};

template <typename Derived>
class ShapeCRTP : public Shape {
public:
    ~ShapeCRTP() override = default;
    void draw() final {
        static_cast<Derived *>(this)->drawImpl();
    }
};

class Square : public ShapeCRTP<Square> {
public:
    void drawImpl() {
        std::cout << "draw a square\n";
    }
};

class Rectangle : public ShapeCRTP<Rectangle> {
public:
    void drawImpl() {
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
