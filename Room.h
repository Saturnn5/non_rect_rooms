#pragma once
#include <vector>

#include "TwoDArray.h"
#include "Utils.h"

class Room {

    unsigned int id;
    unsigned int row;
    unsigned int col;
    unsigned int width;
    unsigned int height;
    std::vector<std::pair<int, int>> walls;

    void drawLine(bool isVert, std::pair<int, int>* wall, std::pair<int, int>* next, TwoDArray& grid) const;
    void reshapeL(RandomGenerator& rg);
    void reshapeU(RandomGenerator& rg);

    public:
    Room(int id, int row, int col, int width, int height, RandomGenerator& rg);
    void fill(TwoDArray& grid);
};
