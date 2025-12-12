// ...existing code...
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include "weapon.h"

class Unit {
public:
    Unit(const std::string& name, int health, int attack, int defense);

    std::string getName() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
    void takeDamage(int damage);
    bool isAlive() const;
    void displayStatus() const;

    // weapon-related
    void addWeapon(const Weapon& weapon);
    std::vector<Weapon> getAvailableWeapons() const;
    void equipWeapon(const Weapon& weapon);
    Weapon getEquippedWeapon() const; // returns a copy; caller should check isAlive etc.

private:
    std::string name;
    int health;
    int attack;
    int defense;
    std::vector<Weapon> weapons;
    int equippedIndex = -1;
};

#endif // UNIT_H
// ...existing code...