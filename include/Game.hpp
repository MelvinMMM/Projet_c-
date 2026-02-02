#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> // Pour std::optional ou std::unique_ptr
#include "Player.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include <SFML/Audio.hpp>

class Game
{
public:
    Game();
    void run();

private:
    sf::Texture bulletTexture; // Texture pour les tirs

   
    void processEvents();
    void update(float dt);
    void render();

    bool isColliding(const sf::Sprite &a, const sf::Sprite &b);
    bool isColliding(const sf::Sprite &a, const sf::CircleShape &b);

    void handleBulletCollisions();
    void handlePlayerCollisions();

    int score = 0;
    sf::Font font;

    // SFML 3 : On utilise std::unique_ptr pour créer le texte APRES avoir chargé la font
    std::unique_ptr<sf::Text> scoreText;
    sf::RectangleShape scoreBox;

    sf::RenderWindow window; // On garde "window" comme dans ton .hpp

    sf::Texture playerTexture;
    std::vector<sf::Texture> asteroidTextures;
    sf::Texture bgTexture;
    sf::RectangleShape bgShape;

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    int lives = 3;
    bool isGameOver = false;

    // --- UI Vie ---
    std::unique_ptr<sf::Text> livesText;

    // --- UI Game Over ---
    sf::RectangleShape gameOverOverlay;
    std::unique_ptr<sf::Text> gameOverTitle;

    sf::RectangleShape restartButton;
    sf::RectangleShape quitButton;
    std::unique_ptr<sf::Text> restartText;
    std::unique_ptr<sf::Text> quitText;

    // --- Musique ---
    sf::Music music;
    sf::Music gameOverMusic;

    // --- Fonctions utiles ---
    void resetGame();

    float invincibilityTimer = 0.0f;
    bool isInvincible = false;
};

#endif