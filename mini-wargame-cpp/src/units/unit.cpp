// ...existing code...
#include "unit.h"
#include <iostream>
#include <algorithm>

Unit::Unit(const std::string& name, int health, int attack, int defense)
    : name(name), health(health), attack(attack), defense(defense) {}

std::string Unit::getName() const {
    return name;
}

int Unit::getHealth() const {
    return health;
}

int Unit::getAttack() const {
    return attack;
}

int Unit::getDefense() const {
    return defense;
}

void Unit::takeDamage(int damage) {
    int effectiveDamage = damage - defense;
    if (effectiveDamage > 0) {
        health -= effectiveDamage;
        std::cout << name << " takes " << effectiveDamage << " damage!" << std::endl;
    } else {
        std::cout << name << " blocks the attack!" << std::endl;
    }
}

bool Unit::isAlive() const {
    return health > 0;
}

void Unit::displayStatus() const {
    std::cout << name << " - Health: " << health << ", Attack: " << attack << ", Defense: " << defense << std::endl;
}

// weapon-related implementations
void Unit::addWeapon(const Weapon& weapon) {
    weapons.push_back(weapon);
    if (equippedIndex == -1) equippedIndex = 0;
}

std::vector<Weapon> Unit::getAvailableWeapons() const {
    return weapons;
}

void Unit::equipWeapon(const Weapon& weapon) {
    // try to find matching weapon by name; if found, set equippedIndex
    for (size_t i = 0; i < weapons.size(); ++i) {
        if (weapons[i].getName() == weapon.getName()) {
            equippedIndex = static_cast<int>(i);
            return;
        }
    }
    // if not found, add it and equip the new one
    weapons.push_back(weapon);
    equippedIndex = static_cast<int>(weapons.size() - 1);
}

Weapon Unit::getEquippedWeapon() const {
    if (equippedIndex >= 0 && equippedIndex < static_cast<int>(weapons.size()))
        return weapons[equippedIndex];
    // return a default Weapon if none equipped
    return Weapon("None", 0, 0);
}
// ...existing code...