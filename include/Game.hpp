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

    sf::RenderWindow m_window;
    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Asteroid> m_asteroids;
};

#endif