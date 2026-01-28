#include "../include/Ennemie.hpp"

Ennemie::Ennemie(std::string n, int f) : nom(n), force(f) {
    std::cout << "Un " << nom << " est genere avec " << force << " points de force." << std::endl;
}

void Ennemie::attaquer(Character &cible) {
    cible.takeDamage(force);
}

Ennemie::~Ennemie() {}

Strong::Strong(int f) : Ennemie("Strong", f) {}
void Strong::attaquer(Character &cible) {
    std::cout << "Strong attaque " << cible.getName() << " !" << std::endl;
    cible.takeDamage(force);
}

Clever::Clever(int f) : Ennemie("Clever", f) {}
void Clever::attaquer(Character &cible) {
    std::cout << "Clever crache du feu sur " << cible.getName() << " !" << std::endl;
    cible.takeDamage(force);
}

Speed::Speed(int f) : Ennemie("Speed", f) {}
void Speed::attaquer(Character &cible) {
    std::cout << "Speed fond sur " << cible.getName() << " !" << std::endl;
    cible.takeDamage(force);
}