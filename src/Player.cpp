#include "../include/Player.hpp"
#include <SFML/System/Angle.hpp>
#include <cmath>

// --- FIX SFML 3 ---
// Cette fonction crée une texture vide qui reste en mémoire.
// Elle sert juste à initialiser le Sprite pour que le code compile.
const sf::Texture& getDummyTexture() {
    static sf::Texture dummy;
    return dummy;
}

// Liste d'initialisation ": sprite(getDummyTexture())"
// C'est OBLIGATOIRE en SFML 3.
Player::Player() : sprite(getDummyTexture()) {
    acceleration = 200.0f;
    friction = 0.98f;
    shootCooldown = 0.f;

    sprite.setPosition({400.f, 300.f});
    // On met l'échelle à 0.1 car ton image ship.png semble grande
    // Tu pourras ajuster ce chiffre (0.2f, 0.5f...) si c'est trop petit
    sprite.setScale({0.4f, 0.4f}); 
}

void Player::setTexture(const sf::Texture& tex) {
    // C'est ici qu'on reçoit la VRAIE image chargée dans Game.cpp
    sprite.setTexture(tex, true); // 'true' pour ajuster la taille du sprite
    
    // On centre l'origine pour que le vaisseau tourne sur lui-même
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Player::update(float dt, const sf::Vector2u& winSize) {
    // Rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) 
        sprite.rotate(sf::degrees(-200.f * dt));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) 
        sprite.rotate(sf::degrees(200.f * dt));

    // Avancer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        float rad = sprite.getRotation().asRadians();
        velocity += sf::Vector2f(std::cos(rad), std::sin(rad)) * acceleration * dt;
    }

    // Physique
    sprite.move(velocity * dt);
    velocity *= friction;

    // Wrapping (Traverser l'écran)
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x > winSize.x) pos.x = 0; else if (pos.x < 0) pos.x = (float)winSize.x;
    if (pos.y > winSize.y) pos.y = 0; else if (pos.y < 0) pos.y = (float)winSize.y;
    sprite.setPosition(pos);

    if (shootCooldown > 0) shootCooldown -= dt;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::resetPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
    velocity = {0.f, 0.f};
}