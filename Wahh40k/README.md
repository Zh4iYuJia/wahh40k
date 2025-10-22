# Wahh40k Game Project

## Overview
Wahh40k is a text-based strategy game inspired by the Warhammer 40,000 universe. Players control units and engage in combat using a turn-based system that incorporates random number generation to simulate dice rolls.

## Game Rules
- Players take turns to perform actions with their units.
- Each unit can either attack or defend during their turn.
- Combat outcomes are determined by random number generation, simulating the unpredictability of dice rolls.
- The game continues until one player has no units left.

## Installation
1. Clone the repository:
   ```
   git clone <repository-url>
   ```
2. Navigate to the project directory:
   ```
   cd Wahh40k
   ```
3. Build the project using CMake:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

## Running the Game
After building the project, you can run the game executable:
```
./Wahh40k
```

## File Structure
- `src/main.cpp`: Entry point of the game.
- `src/base.cpp`: Implements basic game functionalities.
- `src/game.cpp`: Contains the main game logic.
- `src/unit.cpp`: Defines the unit class and its methods.
- `src/mechanics.cpp`: Implements game mechanics and combat calculations.
- `include/base.h`: Declares the interface for basic functionalities.
- `include/game.h`: Declares the interface for game logic.
- `include/unit.h`: Declares the unit class interface.
- `include/mechanics.h`: Declares the interface for game mechanics.
- `tests/test_game.cpp`: Contains unit tests for game logic.
- `CMakeLists.txt`: CMake configuration file.
- `.gitignore`: Lists files and directories to be ignored by version control.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any suggestions or improvements.