#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    // Signatures mises à jour pour les Sprites
    bool isColliding(const sf::Sprite& a, const sf::Sprite& b);
    bool isColliding(const sf::Sprite& a, const sf::CircleShape& b);
    
    void handleBulletCollisions();
    void handlePlayerCollisions();

    sf::RenderWindow m_window;
    
    // Gestionnaire de textures
    sf::Texture m_playerTexture;
    std::vector<sf::Texture> m_asteroidTextures; // Le vecteur !
    sf::Texture m_bgTexture;
    sf::RectangleShape m_bgShape;

    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Asteroid> m_asteroids;
};

#endif