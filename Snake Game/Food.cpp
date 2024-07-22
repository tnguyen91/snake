#include "Food.h"

Food::Food(float blockSize) : blockSize(blockSize) {
    shape.setFillColor(sf::Color::Red);
    shape.setSize(sf::Vector2f(blockSize, blockSize));
    spawn(800, 600);
}

Food::~Food() {}

void Food::spawn(float width, float height) {
    float x = static_cast<float>(rand() % static_cast<int>(width / blockSize)) * blockSize;
    float y = static_cast<float>(rand() % static_cast<int>(height / blockSize)) * blockSize;
    shape.setPosition(x, y);
}

sf::RectangleShape& Food::getShape() {
    return shape;
}
