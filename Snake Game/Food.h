#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Food {
public:
    Food(float blockSize);
    ~Food();

    void spawn(float width, float height);

    sf::RectangleShape& getShape();

private:
    float blockSize;
    sf::RectangleShape shape;
};

#endif