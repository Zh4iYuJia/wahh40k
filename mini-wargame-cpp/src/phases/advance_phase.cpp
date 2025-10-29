// ...existing code...
#include "advance_phase.h"
#include "../game.h"
#include "../units/unit.h"
#include "../utils/rng.h"
#include <iostream>
#include <vector>
#include <random>

// local roll helper to avoid depending on a specific rng namespace
static int rollDice(int lo, int hi) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(gen);
}

AdvancePhase::AdvancePhase(Game* game) : game(game) {}

void AdvancePhase::execute() {
    std::cout << "Advance Phase: Units are moving forward." << std::endl;

    if (game) {
        try {
            std::vector<Unit>& units = game->getUnits();
            for (Unit& unit : units) {
                int moveDistance = rollDice(1, 6); // use local rollDice
                std::cout << unit.getName() << " would move " << moveDistance << " units forward." << std::endl;
            }
        } catch (...) {
            std::cout << "Game::getUnits() not available or threw; skipping actual moves." << std::endl;
        }
    } else {
        std::cout << "No Game instance provided — Advance Phase placeholder (no unit movement executed)." << std::endl;
    }

    std::cout << "Advance Phase completed." << std::endl;
}
// ...existing code...