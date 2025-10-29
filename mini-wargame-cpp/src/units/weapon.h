// ...existing code...
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

class Weapon {
public:
    Weapon(const std::string& name, int damage, int range);

    std::string getName() const;
    int getDamage() const;
    int getRange() const;
    void displayInfo() const;

private:
    std::string name;
    int damage;
    int range;
};

#endif // WEAPON_H
// ...existing code...