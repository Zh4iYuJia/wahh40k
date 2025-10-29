# Mini Wargame (Simple Text Demo)

A minimal C++ text game inspired by tabletop skirmish rules. Two sides (SM and CSM) equip two weapons each and take turns shooting. Dice are simulated (1–6). All in-console, English text.

## Features
- Two units: SM and CSM
- Each unit equips two weapons (slots `a` and `b`)
- Weapon properties: damage, shots, hit threshold (e.g. 4 means 4+ hits)
- Shooting resolves per-shot rolls; output shows each roll and damage calculation
- Weapon catalog can be loaded from `weapons.txt`

## Files
- `base.cpp` — single-file minimal game implementation (interactive)
- `weapons.txt` — optional weapon catalog (one weapon per line)
- `readme.md` — this file

## weapons.txt format
Each non-comment line:  
`Name damage shots hit_threshold`  
Example:
```
# name damage shots hit_threshold
Boltgun 2 1 4
StormBolter 1 4 4
PlasmaGun 3 2 5
```
Lines starting with `#` are treated as comments.

## Build & Run (Windows)

Prerequisites:
- A C++ compiler (g++ / MSVC) supporting C++11
- (Optional) CMake

1. Using g++ (quick):
Open PowerShell or Git Bash in project root and run:
```powershell
g++ -std=c++11 -O2 base.cpp -o mini_wargame.exe
.\mini_wargame.exe
```

2. Using CMake (if you have a CMakeLists):
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
# then run the produced executable (path may vary)
.\Release\mini_wargame.exe
```

If `cmake` is not installed, install it via `winget install Kitware.CMake -e` or use the g++ method.

## How to play (summary)
- On start, if `weapons.txt` is present the game will show a catalog; choose weapon indices (1,2,3...) for slots `a` and `b`.
- On each turn, choose weapon `a` or `b` to fire.
- The program prints each die roll, counts hits (roll >= threshold) and applies damage = hits * weapon.damage.
- Game ends when one unit's HP ≤ 0 or player quits.

## Notes & Troubleshooting
- Save source files as UTF-8 to avoid MSVC C4819 warnings. In VS Code: "Save with Encoding → UTF-8".
- If include paths or header errors occur when integrating into a larger project, ensure `src` is added to include paths or use relative includes.
- Keep `weapons.txt` in the same working directory when running the executable.

## License
Use and modify as you like for learning or prototyping.

The folder mini-wargame-cpp is a fail try please don't use it.