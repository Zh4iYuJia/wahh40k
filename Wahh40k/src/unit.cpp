// ...existing code...
#include <string>
#include <iostream>

class Unit {
public:
    Unit(std::string name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    void attackUnit(Unit& target) {
        int damage = calculateDamage(target);
        target.takeDamage(damage);
        std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }

    std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

private:
    std::string name;
    int health;
    int attack;
    int defense;

    int calculateDamage(const Unit& target) {
        int baseDamage = attack - target.defense;
        return baseDamage > 0 ? baseDamage : 0;
    }
};
// ...existing code...