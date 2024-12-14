#pragma once
#include "TwoDArray.h"
#include "Utils.h"

class Generator
{
    TwoDArray grid;

    const int size;
    const int room_min;
    const int room_max;
    const int gap;
    const int twoGap;
    RandomGenerator rg;

    void round();
    bool placeStuff();
    bool openSpace();
    bool placeThing(char id);

public:
    Generator(int size, int room_min, int room_max, int gap,
              int seed = RandomGenerator().getRandom());
    ~Generator();
    bool generate();
    friend inline std::ostream& operator<<(std::ostream& os, const Generator& data);
};

inline std::ostream& operator<<(std::ostream& os, const Generator& data)
{
    os << "seed: " << data.rg.getSeed() << std::endl;
    os << data.grid;
    return os;
}