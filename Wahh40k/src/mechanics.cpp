#include "mechanics.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void initializeRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int rollDice(int sides) {
    return std::rand() % sides + 1;
}

int calculateAttack(int attackValue) {
    int roll = rollDice(6); // Simulating a 6-sided die roll
    int totalDamage = attackValue + roll;
    std::cout << "Attack roll: " << roll << ", Total damage: " << totalDamage << std::endl;
    return totalDamage;
}

int calculateDefense(int defenseValue) {
    int roll = rollDice(6); // Simulating a 6-sided die roll
    int totalDefense = defenseValue + roll;
    std::cout << "Defense roll: " << roll << ", Total defense: " << totalDefense << std::endl;
    return totalDefense;
}

bool resolveCombat(int attackerAttack, int defenderDefense) {
    int attackTotal = calculateAttack(attackerAttack);
    int defenseTotal = calculateDefense(defenderDefense);
    
    if (attackTotal > defenseTotal) {
        std::cout << "Attack successful!" << std::endl;
        return true; // Attack hits
    } else {
        std::cout << "Attack missed!" << std::endl;
        return false; // Attack misses
    }
}