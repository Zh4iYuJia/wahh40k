// ...existing code...
#ifndef ADVANCE_PHASE_H
#define ADVANCE_PHASE_H

#include "phase_manager.h"
#include <vector>
#include "../units/unit.h"

class Game; // forward declaration

class AdvancePhase : public Phase {
public:
    // allow default nullptr so PhaseManager can construct without args
    AdvancePhase(Game* game = nullptr);
    void execute() override;
    void advanceUnits(std::vector<Unit>& units);

private:
    Game* game;
};

#endif // ADVANCE_PHASE_H
// ...existing code...