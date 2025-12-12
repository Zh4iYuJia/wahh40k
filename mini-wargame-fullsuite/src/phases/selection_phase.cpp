// ...existing code...
#include "selection_phase.h"
#include "../units/unit.h"
#include "../units/weapon.h"
#include "../utils/rng.h"
#include <iostream>
#include <vector>
#include <string>

SelectionPhase::SelectionPhase(Game* game) : game(game) {}

void SelectionPhase::execute() {
    std::cout << "--- Selection Phase ---\n";
    if (game) {
        selectUnits(game->getUnits());
    } else {
        std::cout << "No Game instance provided — Selection Phase placeholder.\n";
    }
}

void SelectionPhase::selectUnits(std::vector<Unit>& availableUnits) {
    std::cout << "Select your units:\n";
    for (size_t i = 0; i < availableUnits.size(); ++i) {
        std::cout << i + 1 << ". " << availableUnits[i].getName() << "\n";
    }
    int choice;
    std::cout << "Enter the number of the unit you want to select: ";
    std::cin >> choice;
    if (choice > 0 && choice <= static_cast<int>(availableUnits.size())) {
        Unit& selectedUnit = availableUnits[choice - 1];
        selectWeapons(selectedUnit);
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void SelectionPhase::selectWeapons(Unit& unit) {
    std::cout << "Select weapons for " << unit.getName() << ":\n";
    std::vector<Weapon> availableWeapons = unit.getAvailableWeapons();
    if (availableWeapons.empty()) {
        std::cout << "No weapons available for this unit.\n";
        return;
    }
    for (size_t i = 0; i < availableWeapons.size(); ++i) {
        std::cout << i + 1 << ". " << availableWeapons[i].getName() << "\n";
    }
    int choice;
    std::cout << "Enter the number of the weapon you want to equip: ";
    std::cin >> choice;
    if (choice > 0 && choice <= static_cast<int>(availableWeapons.size())) {
        unit.equipWeapon(availableWeapons[choice - 1]);
        std::cout << unit.getName() << " has equipped " << availableWeapons[choice - 1].getName() << ".\n";
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}
// ...existing code...