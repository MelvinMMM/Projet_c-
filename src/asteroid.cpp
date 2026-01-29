#include "../include/Asteroid.hpp"
#include "../include/Utils.hpp"
#include <SFML/System/Angle.hpp>

// Initialisation directe ": sprite(tex)"
Asteroid::Asteroid(float x, float y, const sf::Texture& tex) 
    : sprite(tex) 
{
    sprite.setPosition({x, y});
    
    // Ajuste l'échelle selon la taille de tes images Sonic/Asteroid
    sprite.setScale({0.5f, 0.5f}); 

    // Centrage
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    velocity = { randomFloat(-100.f, 100.f), randomFloat(-100.f, 100.f) };
    rotationSpeed = randomFloat(-50.f, 50.f);
}

void Asteroid::update(float dt, const sf::Vector2u& winSize) {
    sprite.move(velocity * dt);
    sprite.rotate(sf::degrees(rotationSpeed * dt));

    sf::Vector2f pos = sprite.getPosition();
    if (pos.x > winSize.x) pos.x = 0;
    else if (pos.x < 0) pos.x = (float)winSize.x;
    
    if (pos.y > winSize.y) pos.y = 0;
    else if (pos.y < 0) pos.y = (float)winSize.y;
    
    sprite.setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}