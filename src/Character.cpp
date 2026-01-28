#include "../include/Character.hpp"
#include <iostream>

Character::Character(const std::string& name, int health, int speed) 
    : name(name), health(health), speed(speed) {}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
    std::cout << name << " perd " << amount << " PV. (Reste: " << health << ")" << std::endl;
}

bool Character::isAlive() const {
    return health > 0;
}

std::string Character::getName() const { return name; }
    int Character::getHealth() const { return health; }
    int Character::getSpeed() const { return speed; }

    Character::~Character() {
            std::cout << "Le personnage " << name << " est détruit." << std::endl;
        }