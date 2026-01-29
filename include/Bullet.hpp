#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifeTime;

    Bullet(sf::Vector2f position, float angleRotation);
    bool update(float dt); // Retourne true si la balle doit mourir
    void draw(sf::RenderWindow& window);
};

#endif