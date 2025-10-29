// ...existing code...
#ifndef SHOOTING_PHASE_H
#define SHOOTING_PHASE_H

#include "phase_manager.h"
#include <vector>
#include "../units/unit.h"
#include "../units/weapon.h"
#include "../utils/rng.h"

class Game;

class ShootingPhase : public Phase {
public:
    ShootingPhase(Game* game = nullptr);
    void execute() override;
    void resolveShooting(std::vector<Unit>& attackers, std::vector<Unit>& defenders);

private:
    Game* game;
};

#endif // SHOOTING_PHASE_H
// ...existing code...