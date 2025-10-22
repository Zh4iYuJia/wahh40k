#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <random>

class Unit {
public:
    Unit(const std::string& name, int health, int attack, int defense);
    
    void attackUnit(Unit& target);
    void takeDamage(int damage);
    bool isAlive() const;

    std::string getName() const;
    int getHealth() const;

private:
    std::string name;
    int health;
    int attack;
    int defense;

    int rollDice(int sides);
};

#endif // UNIT_H