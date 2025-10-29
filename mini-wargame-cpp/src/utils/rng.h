#ifndef RNG_H
#define RNG_H

#include <random>

class RNG {
public:
    static int roll(int sides) {
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 eng(rd());  // Seed the generator
        std::uniform_int_distribution<> distr(1, sides); // Define the range

        return distr(eng); // Generate the random number
    }
};

#endif // RNG_H