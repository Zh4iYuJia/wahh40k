// ...existing code...
#include "game.h"
#include <iostream>
#include <random>
#include <algorithm>

Game::Game()
    : unitAName("astra"), unitAHP(12), unitAAttack(4), unitADef(2),
      unitBName("Chaos marine"), unitBHP(10), unitBAttack(5), unitBDef(1),
      turnA(true) {}

static int rollDie(std::mt19937 &rng) {
    static std::uniform_int_distribution<int> d6(1, 6);
    return d6(rng);
}

void Game::run() {
    std::cout << "Game Start: " << unitAName << " vs " << unitBName << "\n\n";

    std::random_device rd;
    std::mt19937 rng(rd());

    int turn = 1;
    while (unitAHP > 0 && unitBHP > 0) {
        std::cout << "Round " << turn++ << ":\n";
        // 随机决定本回合为射击还是近战（50/50）
        bool shooting = (rollDie(rng) % 2 == 0);

        if (shooting) {
            handleShooting();
        } else {
            handleMelee();
        }

        std::cout << unitAName << " HP: " << unitAHP << " | " << unitBName << " HP: " << unitBHP << "\n";
        std::cout << "--------------------------------\n";

        // 切换先手（可选）
        turnA = !turnA;
    }

    if (unitAHP <= 0 && unitBHP <= 0) {
        std::cout << "Tie\n";
    } else if (unitAHP <= 0) {
        std::cout << unitBName << " Wins!\n";
    } else {
        std::cout << unitAName << " Wins!\n";
    }
}

void Game::handleShooting() {
    // 使用局部 RNG 生成随机数
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::cout << "[Shooting phases] ";
    // 射击：双方各进行一次掷骰比较（更高者造成伤害）
    int aRoll = rollDie(rng) + unitAAttack;
    int bRoll = rollDie(rng) + unitBAttack;
    std::cout << unitAName << " Rolled: " << aRoll << ", "
              << unitBName << " Rolled: " << bRoll << ".\n";

    if (aRoll > bRoll) {
        int damage = std::max(0, aRoll - (unitBDef + (rollDie(rng) % 3))); // 防御有小幅随机
        unitBHP -= damage;
        std::cout << unitAName << " hit " << unitBName << ", deal " << damage << " damage.\n";
    } else if (bRoll > aRoll) {
        int damage = std::max(0, bRoll - (unitADef + (rollDie(rng) % 3)));
        unitAHP -= damage;
        std::cout << unitBName << " hit " << unitAName << ", deal " << damage << " damage.\n";
    } else {
        std::cout << "Tie, no damage\n";
    }

    if (unitAHP < 0) unitAHP = 0;
    if (unitBHP < 0) unitBHP = 0;
}

void Game::handleMelee() {
    // 近战：双方互相攻击，造成较固定但随机范围的伤害
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::cout << "[melee phase]\n";

    // 攻击顺序由 turnA 决定
    auto attackOnce = [&](std::string attacker, int atk, int defTarget, int &hpTarget) {
        int atkRoll = rollDie(rng) + atk;
        int defRoll = rollDie(rng) + defTarget;
        std::cout << attacker << " melee rolled: " << atkRoll << " vs defense rolled: " << defRoll << ".";
        if (atkRoll > defRoll) {
            int damage = std::max(1, atkRoll - defRoll); // 近战至少造成1点伤害
            hpTarget -= damage;
            std::cout << " Hit, deal " << damage << " damage.\n";
        } else {
            std::cout << " Miss.\n";
        }
        if (hpTarget < 0) hpTarget = 0;
    };

    if (turnA) {
        attackOnce(unitAName, unitAAttack, unitBDef, unitBHP);
        if (unitBHP > 0) attackOnce(unitBName, unitBAttack, unitADef, unitAHP);
    } else {
        attackOnce(unitBName, unitBAttack, unitADef, unitAHP);
        if (unitAHP > 0) attackOnce(unitAName, unitAAttack, unitBDef, unitBHP);
    }
}
// ...existing code...