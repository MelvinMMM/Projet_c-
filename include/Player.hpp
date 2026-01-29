#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

struct Player {
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    float acceleration;
    float friction;
    float shootCooldown;

    Player();
    void update(float dt, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window);
};

#endif