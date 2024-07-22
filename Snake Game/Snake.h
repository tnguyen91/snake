#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
    Snake(float blockSize);
    ~Snake();

    void drawSnake(sf::RenderWindow& window);

    void grow();
    void move();
    bool checkCollision();

    float getBlockSize() const;
    sf::Vector2f getDirection() const;
    sf::RectangleShape& getHead();

    void setDirection(float x, float y);

private:
    float blockSize;
    std::vector<sf::RectangleShape> segments;
    sf::Vector2f direction;
};
#endif