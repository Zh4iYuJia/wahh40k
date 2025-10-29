// ...existing code...
#ifndef PHASE_MANAGER_H
#define PHASE_MANAGER_H

class Phase;
class Game;

class PhaseManager {
public:
    PhaseManager(Game* game = nullptr);
    ~PhaseManager();

    void setGame(Game* g);
    void startSelectionPhase();
    void startShootingPhase();
    void startAdvancePhase();

private:
    Phase* currentPhase;
    Game* game;
};

#endif // PHASE_MANAGER_H
// ...existing code...