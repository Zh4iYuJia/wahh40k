#include "weapon.h"
#include <iostream>

Weapon::Weapon(const std::string& name, int damage, int range)
    : name(name), damage(damage), range(range) {}

std::string Weapon::getName() const {
    return name;
}

int Weapon::getDamage() const {
    return damage;
}

int Weapon::getRange() const {
    return range;
}

void Weapon::displayInfo() const {
    std::cout << "Weapon Name: " << name << "\n"
              << "Damage: " << damage << "\n"
              << "Range: " << range << std::endl;
}