#include "../include/Game.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <string>
#include <vector>

Game::Game()
    : window(sf::VideoMode({800u, 600u}), "Asteroids SFML 3 - Sonic Edition")
{
    // 1. MUSIQUE
    if (!music.openFromFile("music/je sais pas trop... 49.mp3"))
    {
        std::cerr << "ERREUR : musique introuvable !" << std::endl;
    }
    music.play();
    music.setVolume(50.f);
    music.setLooping(true);

    // 2. POLICE ET INTERFACE (UI)
    if (!font.openFromFile("assets/SPACE.ttf")) {
        std::cerr << "ERREUR : Police SPACE.ttf introuvable !" << std::endl;
    }

    // On initialise le texte avec la police (Obligatoire en SFML 3)
    scoreText = std::make_unique<sf::Text>(font);
    scoreText->setString("Score: 0");
    scoreText->setCharacterSize(14);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({660.f, 20.f}); 

    // Configuration du carré de fond pour le score
    scoreBox.setSize({140.f, 50.f});
    scoreBox.setFillColor(sf::Color(0, 0, 0, 150)); // Noir transparent
    scoreBox.setOutlineThickness(2);
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setPosition({650.f, 10.f});

    // 3. TEXTURES DU JOUEUR ET ASTÉROÏDES
    if (!playerTexture.loadFromFile("assets/ship.png"))
    {
        std::cerr << "ERREUR: ship.png introuvable !" << std::endl;
    }
    player.setTexture(playerTexture);

    std::vector<std::string> asteroidFiles = {
        "assets/asteroid.png",
        "assets/asteroid2.png",
        "assets/asteroid3.png",
        "assets/asteroid4.png",
        "assets/asteroid5.png",
        "assets/asteroid6.png",
        "assets/asteroid7.png"};

    for (const auto &filename : asteroidFiles)
    {
        sf::Texture tex;
        if (tex.loadFromFile(filename))
        {
            asteroidTextures.push_back(tex);
        }
    }

    // Création des astéroïdes de départ
    for (int i = 0; i < 7; i++)
    {
        if (!asteroidTextures.empty())
        {
            int index = std::rand() % asteroidTextures.size();
            asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600), asteroidTextures[index]);
        }
    }

    // 4. BACKGROUND
    if (!bgTexture.loadFromFile("assets/bg.jpg"))
    {
        std::cerr << "ERREUR : bg.jpg introuvable !" << std::endl;
    }
    bgShape.setSize({800.f, 600.f});
    bgShape.setTexture(&bgTexture);

    // ... à la fin du constructeur ...

// 1. UI des Vies (Haut à gauche)
livesText = std::make_unique<sf::Text>(font);
livesText->setString("Vies: 3");
livesText->setCharacterSize(24);
livesText->setFillColor(sf::Color::Red);
livesText->setPosition({20.f, 20.f});

// 2. Overlay de Game Over (Noir 75% opacité)
gameOverOverlay.setSize({800.f, 600.f});
gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 191)); // 191 = 75% de 255

// 3. Bouton Recommencer
restartButton.setSize({200.f, 50.f});
restartButton.setFillColor(sf::Color::Blue);
restartButton.setPosition({300.f, 250.f});
restartText = std::make_unique<sf::Text>(font);
restartText->setString("RECOMMENCER");
restartText->setCharacterSize(16);
restartText->setPosition({320.f, 260.f});

// 4. Bouton Quitter
quitButton.setSize({200.f, 50.f});
quitButton.setFillColor(sf::Color::Red);
quitButton.setPosition({300.f, 330.f});
quitText = std::make_unique<sf::Text>(font);
quitText->setString("QUITTER");
quitText->setCharacterSize(16);
quitText->setPosition({355.f, 340.f});

// 5. Charger la musique de Game Over
if (!gameOverMusic.openFromFile("music/je sais pas trop... 50.mp3")) { 
    std::cerr << "Musique Game Over introuvable !" << std::endl; 
}
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Game::update(float dt)
{
    if (isGameOver) {
        // Gestion des clics boutons
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            if (restartButton.getGlobalBounds().contains(mousePosF)) {
                resetGame();
            }
            if (quitButton.getGlobalBounds().contains(mousePosF)) {
                window.close();
            }
        }
        return; // On stoppe l'update du jeu
    }

    // Gestion de l'invincibilité
    if (isInvincible) {
        invincibilityTimer -= dt;
        
        // Effet visuel : Clignotement
        // On change l'opacité (Alpha) en fonction du temps
        if (static_cast<int>(invincibilityTimer * 10) % 2 == 0) {
            player.sprite.setColor(sf::Color(255, 255, 255, 100)); // Transparent
        } else {
            player.sprite.setColor(sf::Color(255, 255, 255, 255)); // Opaque
        }

        if (invincibilityTimer <= 0) {
            isInvincible = false;
            player.sprite.setColor(sf::Color::White); // On remet la couleur normale
        }
    }

    player.update(dt, window.getSize());

    // Tirer
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && player.shootCooldown <= 0)
    {
        bullets.emplace_back(player.sprite.getPosition(), player.sprite.getRotation().asDegrees());
        player.shootCooldown = 0.3f;
    }

    // Update Balles
    for (size_t i = 0; i < bullets.size();)
    {
        if (bullets[i].update(dt)) { bullets.erase(bullets.begin() + i); }
        else { i++; }
    }

    // Update Astéroïdes
    for (auto &ast : asteroids)
    {
        ast.update(dt, window.getSize());
    }

    handleBulletCollisions();
    handlePlayerCollisions();
}

void Game::render() {
    window.clear();
    window.draw(bgShape);
    player.draw(window);
    for (auto &b : bullets) b.draw(window);
    for (auto &ast : asteroids) ast.draw(window);
    
    // UI classique
    window.draw(scoreBox);
    window.draw(*scoreText);
    window.draw(*livesText);

    // --- UI GAME OVER ---
    if (isGameOver) {
        window.draw(gameOverOverlay);
        window.draw(restartButton);
        window.draw(quitButton);
        window.draw(*restartText);
        window.draw(*quitText);
    }

    window.display();
}

// --- COLLISIONS ---

bool Game::isColliding(const sf::Sprite &a, const sf::Sprite &b)
{
    return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

bool Game::isColliding(const sf::Sprite &a, const sf::CircleShape &b)
{
    return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

void Game::handleBulletCollisions()
{
    if (isGameOver || isInvincible) return;

    for (const auto &ast : asteroids)
    {
        if (isColliding(player.sprite, ast.sprite))
        {
            lives--;
            livesText->setString("Vies: " + std::to_string(lives));
            player.resetPosition({400.f, 300.f});

            if (lives <= 0) {
                isGameOver = true;
                music.stop();
                gameOverMusic.play();
            } else {
                // ACTIVATION DE L'INVINCIBILITÉ
                isInvincible = true;
                invincibilityTimer = 2.0f; // 2 secondes
            }
            break; // On sort de la boucle pour éviter de perdre plusieurs vies d'un coup
        }
    }
    for (auto itAst = asteroids.begin(); itAst != asteroids.end();)
    {
        bool hit = false;
        for (auto itBull = bullets.begin(); itBull != bullets.end();)
        {
            if (isColliding(itAst->sprite, itBull->shape))
            {
                itBull = bullets.erase(itBull);
                hit = true;
                break;
            }
            else { ++itBull; }
        }

        if (hit)
        {
            // MISE À JOUR SCORE
            score += 10;
            if (scoreText) {
                scoreText->setString("Score: " + std::to_string(score));
            }

            itAst = asteroids.erase(itAst);
            
            // Respawn
            if (!asteroidTextures.empty())
            {
                int index = std::rand() % asteroidTextures.size();
                asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600), asteroidTextures[index]);
            }
        }
        else { ++itAst; }
    }
}

void Game::resetGame() {
    lives = 3;
    score = 0;
    isGameOver = false;
    isInvincible = false;
    invincibilityTimer = 0.0f;
    player.sprite.setColor(sf::Color::White);
    livesText->setString("Vies: 3");
    scoreText->setString("Score: 0");
    
    asteroids.clear();
    bullets.clear();
    player.resetPosition({400.f, 300.f});
    
    // Recréer les astéroïdes
    for (int i = 0; i < 7; i++) {
        int index = std::rand() % asteroidTextures.size();
        asteroids.emplace_back(randomFloat(0, 800), randomFloat(0, 600), asteroidTextures[index]);
    }

    gameOverMusic.stop();
    music.play();
}

void Game::handlePlayerCollisions()
{
    for (const auto &ast : asteroids)
    {
        if (isColliding(player.sprite, ast.sprite))
        {
            player.resetPosition({400.f, 300.f});
            // Optionnel : on pourrait retirer des points ici
        }
    }
}