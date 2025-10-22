#include "game.h"
#include "unit.h"
#include "mechanics.h"
#include <cassert>
#include <iostream>

void testUnitAttack() {
    Unit attacker("Attacker", 10, 5);
    Unit defender("Defender", 10, 3);
    
    int initialDefenderHealth = defender.getHealth();
    attacker.attack(defender);
    
    assert(defender.getHealth() < initialDefenderHealth);
    std::cout << "Unit attack test passed!" << std::endl;
}

void testRandomNumberGeneration() {
    int roll = rollDice(6);
    assert(roll >= 1 && roll <= 6);
    std::cout << "Random number generation test passed!" << std::endl;
}

void testGameLogic() {
    Game game;
    game.initialize();
    
    assert(game.getState() == GameState::RUNNING);
    game.update();
    assert(game.getState() == GameState::RUNNING);
    
    game.end();
    assert(game.getState() == GameState::ENDED);
    std::cout << "Game logic test passed!" << std::endl;
}

int main() {
    testUnitAttack();
    testRandomNumberGeneration();
    testGameLogic();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}