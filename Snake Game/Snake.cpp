#include "Snake.h"

Snake::Snake(float blockSize) : blockSize(blockSize) {
    direction = { blockSize, 0 };
    segments.push_back(sf::RectangleShape(sf::Vector2f(blockSize, blockSize))); 
}

Snake::~Snake() {}

void Snake::drawSnake(sf::RenderWindow& window) {
    for (auto& segment : segments) {
        window.draw(segment);
    }
}

void Snake::grow() {
    segments.push_back(sf::RectangleShape(sf::Vector2f(blockSize, blockSize)));
}

void Snake::move() {
    for (std::size_t i = segments.size() - 1; i > 0; --i) {
        segments[i].setPosition(segments[i - 1].getPosition());
    }
    segments[0].move(direction);
}

bool Snake::checkCollision() {
    // collision with wall
    if (segments[0].getPosition().x < 0 || segments[0].getPosition().x >= 800 ||
        segments[0].getPosition().y < 0 || segments[0].getPosition().y >= 600) {
        return true;
    }

    // collision with self
    for (std::size_t i = 1; i < segments.size(); ++i) {
        if (segments[0].getGlobalBounds().intersects(segments[i].getGlobalBounds())) {
            return true;
        }
    }

    return false;
}

float Snake::getBlockSize() const {
    return blockSize;
}

sf::RectangleShape& Snake::getHead() {
    return segments[0];
}

sf::Vector2f Snake::getDirection() const {
    return direction;
}

void Snake::setDirection(float x, float y) {
    direction.x = x;
    direction.y = y;
}






