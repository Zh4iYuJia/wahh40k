#include <iostream>
#include <cassert>
#include "../src/units/unit.h"
#include "../src/units/weapon.h"
#include "../src/phases/selection_phase.h"
#include "../src/phases/shooting_phase.h"
#include "../src/phases/advance_phase.h"

void testUnitCreation() {
    Unit unit("Space Marine", 100, 10);
    assert(unit.getName() == "Space Marine");
    assert(unit.getHealth() == 100);
    assert(unit.getAttack() == 10);
    std::cout << "Unit creation test passed!" << std::endl;
}

void testWeaponCreation() {
    Weapon weapon("Bolter", 15);
    assert(weapon.getName() == "Bolter");
    assert(weapon.getDamage() == 15);
    std::cout << "Weapon creation test passed!" << std::endl;
}

void testSelectionPhase() {
    SelectionPhase selectionPhase;
    selectionPhase.addUnit("Space Marine");
    selectionPhase.addUnit("Tactical Marine");
    assert(selectionPhase.getAvailableUnits().size() == 2);
    std::cout << "Selection phase test passed!" << std::endl;
}

void testShootingPhase() {
    ShootingPhase shootingPhase;
    Unit attacker("Space Marine", 100, 10);
    Weapon weapon("Bolter", 15);
    int damageDealt = shootingPhase.shoot(attacker, weapon);
    assert(damageDealt == 15);
    std::cout << "Shooting phase test passed!" << std::endl;
}

void testAdvancePhase() {
    AdvancePhase advancePhase;
    Unit unit("Space Marine", 100, 10);
    advancePhase.advance(unit, 5);
    assert(unit.getPosition() == 5);
    std::cout << "Advance phase test passed!" << std::endl;
}

int main() {
    testUnitCreation();
    testWeaponCreation();
    testSelectionPhase();
    testShootingPhase();
    testAdvancePhase();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}