#include "../include/Game.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/System/Angle.hpp>

Game::Game() 
    : m_window(sf::VideoMode({800u, 600u}), "Asteroids SFML 3 - Sonic Edition") 
{
    m_window.setFramerateLimit(60);

    // =========================================
    // 1. CHARGEMENT DES IMAGES
    // =========================================
    
    // Charger le vaisseau
    if (!m_playerTexture.loadFromFile("assets/ship.png")) {
        std::cerr << "ERREUR: Impossible de trouver ship.png (Verifiez le dossier !)" << std::endl;
        // Si ça échoue, on continue (le vaisseau sera un carré blanc, mais ça ne plantera pas)
    }
    m_player.setTexture(m_playerTexture);

    // Charger les astéroïdes (Tu en as 3 différents)
    std::vector<std::string> asteroidFiles = {
        "assets/asteroid.png", 
        "assets/asteroid2.png", 
        "assets/asteroid3.png"
    };

    for (const auto& filename : asteroidFiles) {
        sf::Texture tex;
        if (tex.loadFromFile(filename)) {
            m_asteroidTextures.push_back(tex);
            std::cout << "OK : " << filename << " chargee." << std::endl;
        } else {
            std::cerr << "ERREUR : " << filename << " introuvable." << std::endl;
        }
    }

    // =========================================
    // 2. CREATION DU JEU
    // =========================================

    // On crée 5 astéroïdes
    for(int i = 0; i < 7; i++) {
        if (!m_asteroidTextures.empty()) {
            // On prend une texture au hasard
            int index = std::rand() % m_asteroidTextures.size();
            m_asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600), m_asteroidTextures[index]);
        }
    }
    // =========================================
    // 3. CHARGEMENT DU BACKGROUND
    // =========================================
    if (!m_bgTexture.loadFromFile("assets/bg.jpg")) {
        std::cerr << "ERREUR : background.jpg introuvable !" << std::endl;
    }
    
    // On configure le rectangle pour qu'il fasse la taille de l'écran
    m_bgShape.setSize({800.f, 600.f});
    
    // On applique la texture sur le rectangle
    // Note le '&' : setTexture attend un pointeur vers la texture
    m_bgShape.setTexture(&m_bgTexture);

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
    m_player.update(dt, m_window.getSize());

    // Tirer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && m_player.shootCooldown <= 0) {
        m_bullets.emplace_back(m_player.sprite.getPosition(), m_player.sprite.getRotation().asDegrees());
        m_player.shootCooldown = 0.3f;
    }

    // Mettre à jour les balles
    for (size_t i = 0; i < m_bullets.size(); ) {
        if (m_bullets[i].update(dt)) {
            m_bullets.erase(m_bullets.begin() + i);
        } else {
            i++;
        }
    }

    // Mettre à jour les astéroïdes
    for (auto& ast : m_asteroids) {
        ast.update(dt, m_window.getSize());
    }

    handleBulletCollisions();
    handlePlayerCollisions();
}

void Game::render() {
    m_window.clear(sf::Color::Black);
    m_window.draw(m_bgShape);
    m_player.draw(m_window);
    for (auto& b : m_bullets) b.draw(m_window);
    for (auto& ast : m_asteroids) ast.draw(m_window);
    m_window.display();
}

// --- COLLISIONS ---

bool Game::isColliding(const sf::Sprite& a, const sf::Sprite& b) {
    return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

bool Game::isColliding(const sf::Sprite& a, const sf::CircleShape& b) {
    return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

void Game::handleBulletCollisions() {
    for (auto itAst = m_asteroids.begin(); itAst != m_asteroids.end(); ) {
        bool hit = false;
        for (auto itBull = m_bullets.begin(); itBull != m_bullets.end(); ) {
            if (isColliding(itAst->sprite, itBull->shape)) {
                itBull = m_bullets.erase(itBull);
                hit = true;
                break;
            } else {
                ++itBull;
            }
        }

        if (hit) {
            itAst = m_asteroids.erase(itAst);
            // Respawn
            if (!m_asteroidTextures.empty()) {
                int index = std::rand() % m_asteroidTextures.size();
                m_asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600), m_asteroidTextures[index]);
            }
        } else {
            ++itAst;
        }
    }
}

void Game::handlePlayerCollisions() {
    for (const auto& ast : m_asteroids) {
        if (isColliding(m_player.sprite, ast.sprite)) {
            m_player.resetPosition({400.f, 300.f});
        }
    }
}