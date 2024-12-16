#include "Generator.h"

bool Generator::generate()
{
    round();
    return placeStuff();
}

void Generator::round()
{
    const auto max = static_cast<float>(size);
    const auto center = max / 2.f;
    for (float i = 0; i < max; i++)
    {
        for (float j = 0; j < max; j++)
        {
            auto d = static_cast<float>(sqrt(
                pow(center - (i > center ? i : i + 1), 2) + center
                + pow(center - (j > center ? j : j + 1), 2) + center));
            if (d > center)
            {
                grid.set(i, j, 'X');
            }
        }
    }
}

bool Generator::placeStuff()
{
    int id = 0;
    int retries = 0;
    while (openSpace())
    {
        unless(placeThing(id))
        {
            if (++retries > 5)
            {
                return false;
            }
        } else
        {
            retries = 0;
            if (++id + '0' == 'X')
            {
                id++;
            };

            std::cout<<*this<<std::endl;
        }
    }
    return true;
}

bool Generator::openSpace() const
{
    int max_s = 0;
    for (auto i = 0; i < size; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            int s = 0;
            while (grid.isEmpty(i, j, s, gap))
            {
                s++;
            }
            if (s > max_s)
            {
                max_s = s;
            }
        }
    }
    return max_s > room_min;
}

bool Generator::placeThing(const char id)
{
    const int width = rg.getRandom(room_min, room_max);
    const int height = rg.getRandom(room_min, room_max);

    for (auto i = 0; i < size - height; i++)
    {
        for (auto j = 0; j < size - width; j++)
        {
            if (grid.isEmpty(i, j, width, height, gap))
            {
                rooms.emplace_back(id, i, j, width, height, rg);
                rooms[rooms.size() - 1].draw(grid);
                return true;
            }
        }
    }
    return false;
}

Generator::Generator(const int size, const int room_min, const int room_max,
                     const int gap, const int seed) :
    grid(TwoDArray(size, size)), size(size), room_min(room_min),
    room_max(room_max), gap(gap), twoGap(gap + gap), rg(RandomGenerator(seed))
{
}

Generator::~Generator() = default;