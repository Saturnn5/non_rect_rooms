#include "Room.h"

#include <algorithm>

void Room::drawLine(const bool isVert, std::pair<int, int>* wall, std::pair<int, int>* next, TwoDArray& grid) const
{
    if (isVert)
    {
        int start = std::min(wall->first, next->first);
        int end = std::max(wall->first, next->first);
        for (int i = start; i <= end; i++)
        {
            grid.set(i, wall->second, id + '0');
        }
    }
    else
    {
        int start = std::min(wall->second, next->second);
        int end = std::max(wall->second, next->second);
        for (int j = start; j <= end; j++)
        {
            grid.set(wall->first, j, id + '0');
        }
    }
}

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
    }
    else if (wall == 1)
    {
        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[1].first, c);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(r, walls[2].second);
        newWalls.emplace_back(walls[3]);
    }
    else if (wall == 2)
    {
        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(r, walls[2].second);
        newWalls.emplace_back(r, c);
        newWalls.emplace_back(walls[3].first, c);
    }
    else if (wall == 3)
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

void Room::reshapeU(RandomGenerator& rg)
{
    //minimum interior width of cuts
    //4 means 3 empties between walls
    int min_interior = 3 + 1;
    //minimum size of interior
    //4 means 3 empties between walls
    int min_size = 3 + 1;
    unsigned int wall = rg.getRandom(0, static_cast<int>(walls.size()) - 1);

    //if minimum interior width is too big for the room, decrease it until a cut will fit
    //if the room is so small that the points are forced to generate next to each other, do not create a cut
    while (min_interior > static_cast<int>(wall % 2 == 0 ? height : width) - min_size - min_size)
    {
        if (--min_interior <= 2)
        {
            return;
        }
    }

    std::vector<std::pair<int, int>> newWalls;
    if (wall == 0)
    {
        unsigned int c = rg.getRandom(0, static_cast<int>(width) - min_size - min_size) + col + min_size;
        unsigned int r1 = rg.getRandom(0, static_cast<int>(height) - min_size - min_size - min_interior);
        unsigned int r2 = rg.getRandom(r1 + min_interior, static_cast<int>(height) - min_size - min_size);
        r1 += row + min_size;
        r2 += row + min_size;

        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(r1, walls[0].second);
        newWalls.emplace_back(r1, c);
        newWalls.emplace_back(r2, c);
        newWalls.emplace_back(r2, walls[0].second);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(walls[3]);
    }
    else if (wall == 1)
    {
        unsigned int r = rg.getRandom(0, static_cast<int>(height) - min_size - min_size) + row + min_size;
        unsigned int c1 = rg.getRandom(0, static_cast<int>(width) - min_size - min_size - min_interior);
        unsigned int c2 = rg.getRandom(c1 + min_interior, static_cast<int>(width) - min_size - min_size);
        c1 += col + min_size;
        c2 += col + min_size;

        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[1].first, c1);
        newWalls.emplace_back(r, c1);
        newWalls.emplace_back(r, c2);
        newWalls.emplace_back(walls[1].first, c2);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(walls[3]);
    }
    else if (wall == 2)
    {
        unsigned int c = rg.getRandom(0, static_cast<int>(width) - min_size - min_size) + col + min_size;
        unsigned int r1 = rg.getRandom(0, static_cast<int>(height) - min_size - min_size - min_interior);
        unsigned int r2 = rg.getRandom(r1 + min_interior, static_cast<int>(height) - min_size - min_size);
        r1 += row + min_size;
        r2 += row + min_size;

        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(r2, walls[2].second);
        newWalls.emplace_back(r2, c);
        newWalls.emplace_back(r1, c);
        newWalls.emplace_back(r1, walls[2].second);
        newWalls.emplace_back(walls[3]);
    }
    else if (wall == 3)
    {
        unsigned int r = rg.getRandom(0, static_cast<int>(height) - min_size - min_size) + row + min_size;
        unsigned int c1 = rg.getRandom(0, static_cast<int>(width) - min_size - min_size - min_interior);
        unsigned int c2 = rg.getRandom(c1 + min_interior, static_cast<int>(width) - min_size - min_size);
        c1 += col + min_size;
        c2 += col + min_size;

        newWalls.emplace_back(walls[0]);
        newWalls.emplace_back(walls[1]);
        newWalls.emplace_back(walls[2]);
        newWalls.emplace_back(walls[3]);
        newWalls.emplace_back(walls[3].first, c2);
        newWalls.emplace_back(r, c2);
        newWalls.emplace_back(r, c1);
        newWalls.emplace_back(walls[3].first, c1);
    }
    walls = newWalls;
}

void Room::reshapeO(RandomGenerator& rg)
{
    //minimum interior width of courtyard
    //4 means 3 empties between walls
    int min_interior = 3 + 1;
    //minimum size of interior
    //4 means 3 empties between walls
    int min_size = 3 + 1;

    //if minimum interior width is too big for the room, decrease it until a hole will fit
    //if the room is so small that there is only one valid interior location, do not create a hole
    while (min_interior > static_cast<int>(std::min(width, height)) - min_size - min_size)
    {
        if (--min_interior <= 1)
        {
            return;
        }
    }

    std::vector<std::pair<int, int>> newWalls;

    unsigned int c1 = rg.getRandom(0, static_cast<int>(width) - min_size - min_size - min_interior);
    unsigned int c2 = rg.getRandom(c1 + min_interior, static_cast<int>(width) - min_size - min_size);
    unsigned int r1 = rg.getRandom(0, static_cast<int>(height) - min_size - min_size - min_interior);
    unsigned int r2 = rg.getRandom(r1 + min_interior, static_cast<int>(height) - min_size - min_size);
    r1 += row + min_size;
    r2 += row + min_size;
    c1 += col + min_size;
    c2 += col + min_size;

    newWalls.emplace_back(r1, c1);
    newWalls.emplace_back(r2, c1);
    newWalls.emplace_back(r2, c2);
    newWalls.emplace_back(r1, c2);

    interior_walls = newWalls;
}

void Room::addDoors(RandomGenerator& rg)
{
    int perimeter_len = 0;
    bool isVert = true;
    std::pair<int, int>* wall = nullptr;
    for (auto& next : walls)
    {
        if (wall)
        {
            perimeter_len += isVert ? std::abs(next.first - wall->first) : std::abs(next.second + wall->second);
            isVert = !isVert;
        }
        wall = &next;
    }

    // ReSharper disable once CppDFANullDereference
    perimeter_len += wall->first - walls[0].first;

    //TODO: add doors to the exterior wall

    unless(interior_walls.empty())
    {
        int interior_len = 0;
        for (auto& next : interior_walls)
        {
            if (wall)
            {
                interior_len += isVert ? std::abs(next.first - wall->first) : std::abs(next.second + wall->second);
                isVert = !isVert;
            }
            wall = &next;
        }
        interior_len += wall->first - walls[0].first;
        //TODO: add doors to the interior wall
    }
}

void Room::draw(TwoDArray& grid)
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

    unless(interior_walls.empty())
    {
        for (auto& next : interior_walls)
        {
            if (wall)
            {
                drawLine(isVert, wall, &next, grid);
                isVert = !isVert;
            }
            wall = &next;
        }
        drawLine(isVert, wall, &interior_walls[0], grid);
    }
}

Room::Room(int id, int row, int col, int width, int height, RandomGenerator& rg) :
    id(id), row(row), col(col), width(width), height(height),
    walls({{row, col}, {row + height, col}, {row + height, col + width}, {row, col + width}}), interior_walls()
{
    int chance = rg.getRandom(0, 100);
    if (chance > 75)
    {
        reshapeL(rg);
    }
    else if (chance > 50)
    {
        reshapeU(rg);
    }
    else if (chance > 35)
    {
        reshapeO(rg);
    }
}
