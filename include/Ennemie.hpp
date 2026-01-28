#ifndef ENNEMIE_HPP
#define ENNEMIE_HPP

#include <iostream>
#include <string>
#include "Character.hpp"

class Ennemie {
    public:
        std::string nom;
        int force;

        Ennemie(std::string n, int f);
        virtual void attaquer(Character &cible);
        virtual ~Ennemie();
};

class Strong : public Ennemie {
    public:
        Strong(int f);
        void attaquer(Character &cible);
};

class Clever : public Ennemie {
    public:
        Clever(int f);
        void attaquer(Character &cible);
};

class Speed : public Ennemie {
    public:
        Speed(int f);
        void attaquer(Character &cible);
};

#endif