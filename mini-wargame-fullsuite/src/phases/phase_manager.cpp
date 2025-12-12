// ...existing code...
#include "phase_manager.h"
#include "selection_phase.h"
#include "shooting_phase.h"
#include "advance_phase.h"
#include <iostream>

PhaseManager::PhaseManager(Game* game) : currentPhase(nullptr), game(game) {}

PhaseManager::~PhaseManager() {
    if (currentPhase) delete currentPhase;
}

void PhaseManager::setGame(Game* g) { game = g; }

void PhaseManager::startSelectionPhase() {
    currentPhase = new SelectionPhase(game);
    currentPhase->execute();
    delete currentPhase;
    currentPhase = nullptr;
}

void PhaseManager::startShootingPhase() {
    currentPhase = new ShootingPhase(game);
    currentPhase->execute();
    delete currentPhase;
    currentPhase = nullptr;
}

void PhaseManager::startAdvancePhase() {
    currentPhase = new AdvancePhase(game);
    currentPhase->execute();
    delete currentPhase;
    currentPhase = nullptr;
}
// ...existing code...