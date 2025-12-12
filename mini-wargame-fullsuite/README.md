# Mini Wargame C++ Project

## Overview
This project is a simple mini wargame inspired by the Warhammer 40k universe. Players can select units, equip them with ranged and melee weapons, and engage in various phases of gameplay including shooting and advancing.

## Project Structure
The project is organized into several directories and files:

- **src/**: Contains the source code for the game.
  - **main.cpp**: Entry point of the game.
  - **game.cpp** and **game.h**: Implementation and declaration of the Game class.
  - **phases/**: Contains files for different phases of the game.
    - **selection_phase.cpp** and **selection_phase.h**: Handle unit selection.
    - **shooting_phase.cpp** and **shooting_phase.h**: Manage shooting actions.
    - **advance_phase.cpp** and **advance_phase.h**: Manage unit movement.
    - **phase_manager.cpp**: Coordinates the different phases.
  - **units/**: Contains files related to game units and weapons.
    - **unit.cpp** and **unit.h**: Implementation and declaration of the Unit class.
    - **weapon.cpp** and **weapon.h**: Implementation and declaration of the Weapon class.
  - **utils/**: Contains utility functions.
    - **rng.cpp** and **rng.h**: Random number generator for simulating dice rolls.

- **include/**: Contains public headers for the game.

- **data/**: Contains JSON files for unit and weapon data.

- **tests/**: Contains unit tests for the game components.

- **CMakeLists.txt**: Build configuration file.

- **.gitignore**: Specifies files to ignore in version control.

- **README.md**: Documentation for the project.

## Gameplay
1. **Unit Selection**: Players can choose their units and equip them with weapons.
2. **Shooting Phase**: Players can perform shooting actions using their equipped ranged weapons.
3. **Advance Phase**: Players can move their units on the battlefield.

## Setup Instructions
1. Clone the repository.
2. Navigate to the project directory.
3. Use CMake to build the project:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Run the game:
   ```
   ./mini-wargame
   ```

## Future Enhancements
- Add more unit types and weapons.
- Implement a more complex game logic.
- Improve the user interface for better interaction.

## License
This project is licensed under the MIT License.