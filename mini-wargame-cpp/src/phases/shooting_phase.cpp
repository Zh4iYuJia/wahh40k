// ...existing code...
#include "shooting_phase.h"
#include "../units/unit.h"
#include "../units/weapon.h"
#include "../utils/rng.h"
#include <iostream>
#include <vector>
#include <random>

ShootingPhase::ShootingPhase(Game* game) : game(game) {}

// local roll helper
static int rollDice(int lo, int hi) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(gen);
}

void ShootingPhase::execute() {
    std::cout << "--- Shooting Phase ---\n";
    if (game) {
        auto& units = game->getUnits();
        // demo: use all units as attackers and defenders (replace with actual lists later)
        resolveShooting(units, units);
    } else {
        std::cout << "ShootingPhase executed (placeholder). Use resolveShooting(attackers, defenders) to resolve.\n";
    }
}

void ShootingPhase::resolveShooting(std::vector<Unit>& attackers, std::vector<Unit>& defenders) {
    for (Unit& attacker : attackers) {
        if (!attacker.isAlive()) continue;

        Weapon weapon = attacker.getEquippedWeapon();
        if (weapon.getName() == "None") {
            std::cout << attacker.getName() << " has no equipped weapon, skips shooting.\n";
            continue;
        }

        Unit* target = nullptr;
        for (Unit& d : defenders) {
            if (d.isAlive()) { target = &d; break; }
        }
        if (!target) {
            std::cout << "No alive defenders remain.\n";
            return;
        }

        int roll = rollDice(1, 6);
        int attackValue = attacker.getAttack();
        int defenseValue = target->getDefense();

        std::cout << attacker.getName() << " fires " << weapon.getName() << " at " << target->getName()
                  << " (roll " << roll << ", atk " << attackValue << ", def " << defenseValue << ")\n";

        if (roll + attackValue - defenseValue >= 5) {
            int dmg = weapon.getDamage();
            std::cout << "Hit! " << target->getName() << " takes " << dmg << " damage.\n";
            target->takeDamage(dmg);
            if (!target->isAlive()) std::cout << target->getName() << " is destroyed.\n";
        } else {
            std::cout << "Missed.\n";
        }
    }
}
 // ...existing code...