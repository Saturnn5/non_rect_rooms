#include "Room.h"

void Room::reshapeL(RandomGenerator& rg)
{
    int min_size = 3;
    if (width <= min_size + min_size || height <= min_size + min_size)
    {
        return;
    }
    unsigned int wall = rg.getRandom(0, static_cast<int>(walls.size()) - 1);
    unsigned int c = col + rg.getRandom(min_size, static_cast<int>(width) - min_size);
    unsigned int r = row + rg.getRandom(min_size, static_cast<int>(height) - min_size);

    std::vector<std::pair<int, int>> newWalls;
    if (wall == 0)
    {
        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(r, walls[0].second);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(walls[1].first, c);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(walls[3]);
    } else if (wall == 1)
    {
        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[1].first, c);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(r, walls[2].second);
        newWalls.emplace_back(walls[3]);
    } else if (wall == 2)
    {
        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(r, walls[2].second);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(walls[3].first, c);
    } else if (wall == 3)
    {
        newWalls.emplace_back(walls[3].first, c);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(r, walls[0].second);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(walls[3]);
    }
    walls = newWalls;
}

void Room::fill(TwoDArray& grid)
{
    bool isVert = true;
    std::pair<int, int>* wall = nullptr;
    for (auto& next : walls)
    {
        if (wall)
        {
            drawLine(isVert, wall, &next, grid);
            isVert = !isVert;
        }
        wall = &next;
    }
    drawLine(isVert, wall, &walls[0], grid);
}

void Room::drawLine(const bool isVert, std::pair<int, int>* wall, std::pair<int, int>* next, TwoDArray& grid)
{
    if (isVert)
    {
        int start = std::min(wall->first, next->first);
        int end = std::max(wall->first, next->first);
        for (int i = start; i <= end; i++)
        {
            grid.set(i, wall->second, id + '0');
        }
    } else
    {
        int start = std::min(wall->second, next->second);
        int end = std::max(wall->second, next->second);
        for (int j = start; j <= end; j++)
        {
            grid.set(wall->first, j, id + '0');
        }
    }
}

Room::Room(int id, int row, int col, int width, int height, RandomGenerator& rg) :
    id(id), row(row), col(col), width(width), height(height),
    walls({{row, col}, {row + height, col}, {row + height, col + width}, {row, col + width}})
{
    if (rg.getRandom(0, 100) > 75) {
        reshapeL(rg);
    }
}