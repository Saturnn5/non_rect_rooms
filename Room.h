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

    void reshapeL(RandomGenerator& rg);
    void drawLine(const bool isVert, std::pair<int, int>* wall, std::pair<int, int>* next, TwoDArray& grid);

    public:
    Room(int id, int row, int col, int width, int height, RandomGenerator& rg);
    void fill(TwoDArray& grid);
};
