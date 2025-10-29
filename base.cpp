#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>


using namespace std;
//data structures
struct Weapon {
    string name;
    int damage = 0;
    int shots = 0;
    int hit_threshold = 4; // roll >= hit_threshold counts as hit
};

struct Unit {
    string name;
    int hp = 10;
    Weapon a;
    Weapon b;
};
//dice simulation
static std::mt19937& rng() {
    static thread_local std::mt19937 gen((std::random_device())());
    return gen;
}

int rollDie() {
    std::uniform_int_distribution<int> dist(1, 6);
    return dist(rng());
}
//game logic
void inputWeapon(Weapon& w, const string& label) {
    cout << "Configure weapon " << label << " (damage shots hit_threshold(2-6)): \n";
    cout << "Damage: ";
    while (!(cin >> w.damage) || w.damage < 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter non-negative integer for damage: ";
    }
    cout << "Shots: ";
    while (!(cin >> w.shots) || w.shots < 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter non-negative integer for shots: ";
    }
    cout << "Hit threshold (e.g. 4 means 4+ hits): ";
    while (!(cin >> w.hit_threshold) || w.hit_threshold < 2 || w.hit_threshold > 6) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter integer between 2 and 6: ";
    }
}

void resolveShooting(Unit& attacker, Unit& defender, const Weapon& w) {
    cout << attacker.name << " fires weapon " << w.name << " (" << w.shots << " shots, damage " << w.damage
         << ", hit " << w.hit_threshold << "+)\n";
    if (w.shots <= 0) {
        cout << "No shots to fire.\n";
        return;
    }
    vector<int> rolls;
    rolls.reserve(w.shots);
    for (int i = 0; i < w.shots; ++i) rolls.push_back(rollDie());

    // print rolls
    for (size_t i = 0; i < rolls.size(); ++i) {
        if (i) cout << " ";
        cout << rolls[i];
    }
    cout << "\n";

    int hits = 0;
    for (int r : rolls) if (r >= w.hit_threshold) ++hits;

    int totalDamage = hits * w.damage;
    cout << "Hits: " << hits << " -> total damage = " << totalDamage << "\n";

    if (totalDamage > 0) {
        defender.hp = max(0, defender.hp - totalDamage);
        cout << defender.name << " HP is now " << defender.hp << "\n";
    } else {
        cout << "No damage inflicted.\n";
    }
}

int main() {
    cout << "Simple Mini Wargame: SM vs CSM\n";
    Unit sm{"SM", 20}, csm{"CSM", 20};

    // cout << "Configure weapons for SM (two weapons a and b):\n";
    // sm.a.name = "a";
    // inputWeapon(sm.a, "a");
    // sm.b.name = "b";
    // inputWeapon(sm.b, "b");

    // cout << "Configure weapons for CSM (two weapons a and b):\n";
    // csm.a.name = "a";
    // inputWeapon(csm.a, "a");
    // csm.b.name = "b";
    // inputWeapon(csm.b, "b");

// replace interactive configure block with catalog-based selection
    auto loadCatalog = [](const std::string& path) {
      std::vector<Weapon> catalog;
        std::ifstream fin(path);
        if (!fin) return catalog;
        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            if (line[0] == '#' ) continue; // comment
            std::istringstream iss(line);
            Weapon w;
            if (!(iss >> w.name >> w.damage >> w.shots >> w.hit_threshold)) continue;
            catalog.push_back(w);
        }
        return catalog;
    };

    auto chooseTwoFromCatalog = [&](Unit& unit, const std::vector<Weapon>& catalog, const std::string& unitLabel){
        if (catalog.empty()) {
            std::cout << "Weapon catalog is empty. Falling back to manual configure.\n";
            unit.a.name = "a"; inputWeapon(unit.a, "a");
            unit.b.name = "b"; inputWeapon(unit.b, "b");
            return;
        }
        std::cout << "Available weapons for " << unitLabel << ":\n";
        for (size_t i = 0; i < catalog.size(); ++i) {
            const auto& w = catalog[i];
            std::cout << i + 1 << ". " << w.name << "  dmg:" << w.damage << "  shots:" << w.shots << "  hit:" << w.hit_threshold << "+\n";
        }
        auto pickIndex = [&](const char* prompt) {
            int idx;
            std::cout << prompt;
            while (!(std::cin >> idx) || idx < 1 || idx > static_cast<int>(catalog.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid. Enter a number between 1 and " << catalog.size() << ": ";
            }
        return idx - 1;
    };
    int i1 = pickIndex("Choose weapon for slot a (enter number): ");
    int i2 = pickIndex("Choose weapon for slot b (enter number): ");
    unit.a = catalog[i1]; unit.a.name = "a";
    unit.b = catalog[i2]; unit.b.name = "b";
};

// load catalog from file (weapons.txt in working directory)
std::vector<Weapon> catalog = loadCatalog("weapons.txt");

// configure SM and CSM by choosing from catalog (or fallback)
chooseTwoFromCatalog(sm, catalog, "SM");
chooseTwoFromCatalog(csm, catalog, "CSM");
// ...existing code...

    cout << "\nGame start! SM HP: " << sm.hp << " | CSM HP: " << csm.hp << "\n";

    bool smTurn = true;
    while (sm.hp > 0 && csm.hp > 0) {
        Unit& attacker = smTurn ? sm : csm;
        Unit& defender = smTurn ? csm : sm;

        cout << "\nIt's " << attacker.name << "'s turn. Choose weapon (a/b) or q to quit: ";
        char choice;
        cin >> choice;
        if (choice == 'q' || choice == 'Q') {
            cout << "Quitting game.\n";
            return 0;
        }
        Weapon *wptr = nullptr;
        if (choice == 'a' || choice == 'A') wptr = &attacker.a;
        else if (choice == 'b' || choice == 'B') wptr = &attacker.b;
        else {
            cout << "Invalid choice, try again.\n";
            continue;
        }
        resolveShooting(attacker, defender, *wptr);

        if (defender.hp <= 0) {
            cout << defender.name << " has been defeated. " << attacker.name << " wins!\n";
            break;
        }

        // switch turn
        smTurn = !smTurn;
    }

    cout << "Game over.\n";
    return 0;
}