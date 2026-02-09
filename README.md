# Asteroids SFML 3 - Sonic Edition

## 📖 Description
**Asteroids SFML 3 - Sonic Edition** est un jeu d'arcade 2D développé en **C++** (Standard 17) utilisant la bibliothèque **SFML 3.0.2** Ce projet a été réalisé en binôme dans le cadre de l'évaluation finale "Projet C++ & POO" de la formation Jedy.

Le but est de piloter un vaisseau spatial, de détruire des astéroïdes pour accumuler des points, tout en survivant aux collisions. Cette version intègre une ambiance sonore et visuelle inspirée de l'univers de Sonic.

## 👥 Auteurs et Rôles
Ce projet a été réalisé par :

* **Melvin Mateta**
* **Matthieu Achy**

## 🎮 Fonctionnalités
* **Gameplay Arcade :** Physique de mouvement avec inertie et friction.
* **Système de combat :** Tirs de projectiles et destruction d'astéroïdes.
* **Gestion de vie et Score :** Système de vies, score dynamique et invincibilité temporaire après un impact.
* **Audio :** Musique de fond et bruitages (tirs, game over).
* **Ecran de fin :** Menu Game Over interactif avec options "Recommencer" ou "Quitter".
* **Screen Wrapping :** Les entités qui sortent de l'écran réapparaissent du côté opposé.

## ⚙️ Prérequis Techniques
[cite_start]Conformément aux contraintes du sujet:
* **Langage :** C++17
* **Bibliothèque :** SFML 3.0.2 (Minimum requis)
* **Système :** Compatible Windows (MinGW), macOS et Linux via le Makefile fourni.

## 🛠️ Installation et Compilation
Le projet utilise un **Makefile** pour automatiser la compilation. Assurez-vous d'avoir `g++` et les bibliothèques SFML installées.

### Commandes principales :
* [cite_start]`make` : Compile le projet et génère l'exécutable `Asteroid.exe` (ou `Asteroid` sous Linux/Mac).
* [cite_start]`make re` : Recompile l'intégralité du projet à zéro (utile en cas de problème de lien).
* [cite_start]`make clean` : Supprime les fichiers objets (`.o`).
* [cite_start]`make fclean` : Supprime les fichiers objets et l'exécutable.

## 🕹️ Commandes de Jeu
* **Flèche HAUT (↑)** : Activer les propulseurs (Avancer).
* **Flèche GAUCHE (←) / DROITE (→)** : Pivoter le vaisseau.
* **ESPACE** : Tirer.
* **SOURIS (Clic Gauche)** : Interagir avec les boutons du menu Game Over.

## 📂 Structure du Projet
* `src/` : Contient les fichiers sources (.cpp).
* `include/` : Contient les fichiers d'en-tête (.hpp).
* `assets/` : Images et polices (Vaisseau, Astéroïdes, Fond).
* `music/` : Fichiers audio.
* `lib/` : Bibliothèques statiques pour la compilation.

---
[cite_start]*Projet validé pour la session de Février 2026.*