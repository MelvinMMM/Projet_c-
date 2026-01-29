#include "../include/Player.hpp"
#include <SFML/System/Angle.hpp>
#include <cmath>

Player::Player() {
    acceleration = 200.0f;
    friction = 0.98f;
    shootCooldown = 0.f;

    shape.setPointCount(3);
    shape.setPoint(0, {20.f, 0.f});
    shape.setPoint(1, {-15.f, 10.f});
    shape.setPoint(2, {-15.f, -10.f});
    
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    
    shape.setPosition({400.f, 300.f});
}

void Player::update(float dt, const sf::Vector2u& winSize) {
    // Rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) 
        shape.rotate(sf::degrees(-200.f * dt));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) 
        shape.rotate(sf::degrees(200.f * dt));

    // Avancer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        float rad = shape.getRotation().asRadians();
        velocity += sf::Vector2f(std::cos(rad), std::sin(rad)) * acceleration * dt;
    }

    // Physique
    shape.move(velocity * dt);
    velocity *= friction;

    // Wrapping
    sf::Vector2f pos = shape.getPosition();
    if (pos.x > winSize.x) pos.x = 0; else if (pos.x < 0) pos.x = (float)winSize.x;
    if (pos.y > winSize.y) pos.y = 0; else if (pos.y < 0) pos.y = (float)winSize.y;
    shape.setPosition(pos);

    if (shootCooldown > 0) shootCooldown -= dt;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}