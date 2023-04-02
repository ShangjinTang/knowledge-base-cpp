#include <iostream>
#include <variant>
#include <vector>

class Circle {
public:
    explicit Circle(double radius) : radius_(radius) {}
    [[nodiscard]] double getRadius() const noexcept {
        return radius_;
    }

private:
    double radius_;
};

class Square {
public:
    explicit Square(double side) : side_(side) {}
    [[nodiscard]] double getSide() const noexcept {
        return side_;
    }

private:
    double side_;
};

class Draw {
public:
    void operator()(const Circle& circle) const {
        std::cout << "Drawing circle with radius " << circle.getRadius() << std::endl;
    };
    void operator()(const Square& square) const {
        std::cout << "Drawing square with side " << square.getSide() << std::endl;
    };
};

using Shape = std::variant<Circle, Square>;

void drawAllShapes(std::vector<Shape> const& shapes) {
    for (auto const& s : shapes) {
        std::visit(Draw{}, s);
    }
}

int main() {
    using Shapes = std::vector<Shape>;
    Shapes shapes;
    shapes.emplace_back(Circle{2.0});
    shapes.emplace_back(Square{1.5});
    drawAllShapes(shapes);

    return 0;
}
