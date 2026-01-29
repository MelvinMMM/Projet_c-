#include "../include/Game.hpp"
#include "../include/Utils.hpp"
#include <optional>

Game::Game() 
    : m_window(sf::VideoMode({800u, 600u}), "Asteroids SFML 3") 
{
    m_window.setFramerateLimit(60);
    
    // Création initiale des astéroïdes
    for(int i = 0; i < 5; i++) {
        m_asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600));
    }
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Game::update(float dt) {
    // Update du joueur
    m_player.update(dt, m_window.getSize());

    // Gestion du tir (Logique dans Game pour accéder à la liste des balles)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && m_player.shootCooldown <= 0) {
        m_bullets.emplace_back(m_player.shape.getPosition(), m_player.shape.getRotation().asDegrees());
        m_player.shootCooldown = 0.3f;
    }

    // Update Balles
    for (size_t i = 0; i < m_bullets.size(); ) {
        if (m_bullets[i].update(dt)) {
            m_bullets.erase(m_bullets.begin() + i);
        } else {
            i++;
        }
    }

    // Update Astéroïdes
    for (auto& ast : m_asteroids) {
        ast.update(dt, m_window.getSize());
    }
}

void Game::render() {
    m_window.clear(sf::Color::Black);
    
    m_player.draw(m_window);
    for (auto& b : m_bullets) b.draw(m_window);
    for (auto& ast : m_asteroids) ast.draw(m_window);
    
    m_window.display();
}