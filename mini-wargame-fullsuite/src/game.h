// ...existing code...
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "phases/phase_manager.h"
#include "units/unit.h"

class PhaseManager;

class Game {
public:
    Game();
    ~Game();

    void start();

    // expose units for phases like AdvancePhase (returns reference)
    std::vector<Unit>& getUnits();

private:
    void gameLoop();
    bool continueGame();

    PhaseManager* phaseManager;
    std::vector<Unit> units; // simple storage of units
};

#endif // GAME_H
// ...existing code...