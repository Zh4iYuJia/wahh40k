// ...existing code...
#ifndef SELECTION_PHASE_H
#define SELECTION_PHASE_H

#include "phase_manager.h"
#include <vector>
#include <string>
#include "../units/unit.h"
#include "../units/weapon.h"
#include "../utils/rng.h"

class Game;

class SelectionPhase : public Phase {
public:
    SelectionPhase(Game* game = nullptr);
    void execute() override;
    void selectUnits(std::vector<Unit>& availableUnits);
    void selectWeapons(Unit& unit);

private:
    Game* game;
};

#endif // SELECTION_PHASE_H
// ...existing code...