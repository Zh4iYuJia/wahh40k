// ...existing code...
#pragma once
#include <string>

class Game {
public:
    Game();
    void run();

private:
    void handleShooting();
    void handleMelee();

    // 简化单位状态（保存在 Game 内部以避免依赖外部 unit.h）
    std::string unitAName;
    int unitAHP;
    int unitAAttack;
    int unitADef;

    std::string unitBName;
    int unitBHP;
    int unitBAttack;
    int unitBDef;

    bool turnA; // true = A 先手，false = B 先手
};
// ...existing code...