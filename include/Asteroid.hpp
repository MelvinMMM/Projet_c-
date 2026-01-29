#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <SFML/Graphics.hpp>

struct Asteroid {
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float rotationSpeed;

    Asteroid(float x, float y);
    void update(float dt, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window);
};

#endif