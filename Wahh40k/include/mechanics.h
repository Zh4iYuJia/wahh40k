#ifndef MECHANICS_H
#define MECHANICS_H

#include <cstdlib>
#include <ctime>

class Mechanics {
public:
    Mechanics() {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random number generation
    }

    int rollDice(int sides) {
        return (std::rand() % sides) + 1; // Roll a dice with the given number of sides
    }

    int calculateAttack(int attackPower) {
        int roll = rollDice(6); // Simulate a 6-sided dice roll for attack
        return attackPower + roll; // Return total attack value
    }

    int calculateDefense(int defensePower) {
        int roll = rollDice(6); // Simulate a 6-sided dice roll for defense
        return defensePower + roll; // Return total defense value
    }

    bool resolveCombat(int attackerPower, int defenderPower) {
        int attackValue = calculateAttack(attackerPower);
        int defenseValue = calculateDefense(defenderPower);
        return attackValue > defenseValue; // Return true if attack is successful
    }
};

#endif // MECHANICS_H