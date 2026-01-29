#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "Ennemie.hpp"


int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    Character joueur("Hero", 100, 50);
    
    std::vector<Ennemie*> donjon;
    donjon.push_back(new Strong(15));
    donjon.push_back(new Speed(10));
    donjon.push_back(new Clever(25)); 
    std::cout << "--- BIENVENUE DANS L'ARENE ---" << std::endl;

    for (Ennemie* adversaire : donjon) {
        if (!joueur.isAlive()) break;

        std::cout << "\n>>> Un " << adversaire->nom << " barre la route !" << std::endl;

        while (adversaire->force > 0 && joueur.isAlive()) {
            std::cout << "\n(A)ttaquer ou (P)asser le tour ? ";
            char choix;
            std::cin >> choix;

            if (choix == 'A' || choix == 'a') {
                std::cout << "Vous frappez le " << adversaire->nom << " !" << std::endl;
                adversaire->force -= 5; 
                if (adversaire->force <= 0) {
                    std::cout << "Le " << adversaire->nom << " est vaincu !" << std::endl;
                    break;
                }
            }

            adversaire->attaquer(joueur);

            if (!joueur.isAlive()) {
                std::cout << "Le Hero est tombe au combat..." << std::endl;
                break;
            }
        }
    }

    if (joueur.isAlive()) {
        std::cout << "\nFELICITATIONS ! Vous avez nettoye le donjon !" << std::endl;
    }

    for (Ennemie* e : donjon) {
        delete e;
    }
    donjon.clear();

    return 0;
}