#include "../include/Bullet.hpp"
#include "../include/Utils.hpp"
#include <SFML/System/Angle.hpp>
#include <cmath>

// Constructeur
Bullet::Bullet(sf::Vector2f position, float angleRotation) {
    lifeTime = 0.f;
    shape.setRadius(2.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);

    float speed = 400.f;
    // Conversion degrés -> radians
    float rad = degToRad(angleRotation);
    velocity = { std::cos(rad) * speed, std::sin(rad) * speed };
}

// Mise à jour
bool Bullet::update(float dt) {
    shape.move(velocity * dt);
    lifeTime += dt;
    return lifeTime > 2.0f; // Meurt après 2 secondes
}

// Dessin
void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}