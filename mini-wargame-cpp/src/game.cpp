// ...existing code...
#include "game.h"
#include "phases/phase_manager.h"
#include <iostream>

Game::Game() : phaseManager(new PhaseManager(this)) {
    units.emplace_back("Infantry", 10, 5, 2);
    units.emplace_back("Ranger", 8, 6, 1);
}

Game::~Game() {
    delete phaseManager;
}

void Game::start() {
    std::cout << "Welcome to the Mini Wargame!" << std::endl;
    gameLoop();
}

void Game::gameLoop() {
    while (true) {
        // simple cycle through phases
        phaseManager->startSelectionPhase();
        if (!continueGame()) break;

        phaseManager->startShootingPhase();
        if (!continueGame()) break;

        phaseManager->startAdvancePhase();
        if (!continueGame()) break;
    }
    std::cout << "Thank you for playing!" << std::endl;
}

bool Game::continueGame() {
    char choice;
    std::cout << "Do you want to continue to the next phase? (y/n): ";
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

std::vector<Unit>& Game::getUnits() {
    return units;
}
// ...existing code...