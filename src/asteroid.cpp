#include "../include/Asteroid.hpp"
#include "../include/Utils.hpp"
#include <SFML/System/Angle.hpp>

Asteroid::Asteroid(float x, float y) {
    shape.setSize({40.f, 40.f});
    shape.setOrigin({20.f, 20.f});
    shape.setPosition({x, y});
    
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);

    velocity = { randomFloat(-100.f, 100.f), randomFloat(-100.f, 100.f) };
    rotationSpeed = randomFloat(-50.f, 50.f);
}

void Asteroid::update(float dt, const sf::Vector2u& winSize) {
    shape.move(velocity * dt);
    shape.rotate(sf::degrees(rotationSpeed * dt));

    // Screen Wrapping
    sf::Vector2f pos = shape.getPosition();
    if (pos.x > winSize.x) pos.x = 0;
    else if (pos.x < 0) pos.x = (float)winSize.x;
    
    if (pos.y > winSize.y) pos.y = 0;
    else if (pos.y < 0) pos.y = (float)winSize.y;
    
    shape.setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(shape);
}