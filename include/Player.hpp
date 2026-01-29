#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

struct Player {
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float acceleration;
    float friction;
    float shootCooldown;

    Player();
    void setTexture(const sf::Texture& tex);
    void resetPosition(sf::Vector2f pos);
    void update(float dt, const sf::Vector2u& winSize);
    void draw(sf::RenderWindow& window);
};

#endif