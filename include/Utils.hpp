#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>
#include <cmath>
#include <SFML/System/Vector2.hpp>

// Génère un float aléatoire
inline float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Fonction pour convertir les degrés en radians (utile pour cos/sin)
inline float degToRad(float deg) {
    return deg * 0.0174532925f;
}

#endif