#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Character.hpp"

int main() {
    
    std::vector<Character> enemies;
    enemies.push_back(Character("Gobelin Rapide", 30, 80));
    enemies.push_back(Character("Orque Lent", 60, 20));
    enemies.push_back(Character("Troll Moyen", 100, 50));

    std::sort(enemies.begin(), enemies.end(), [](const Character& a, const Character& b) {
        return a.getSpeed() > b.getSpeed();
    });


}