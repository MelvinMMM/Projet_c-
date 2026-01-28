#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character {
private:
    std::string name;
    int health;
    int speed;

public:
    Character(const std::string &name, int health, int speed);
    
    void takeDamage(int amount);
    bool isAlive() const;

    std::string getName() const;
    int getHealth() const;
    int getSpeed() const;

    ~Character();
};

#endif