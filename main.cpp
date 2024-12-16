#include "Generator.h"

int main()
{
    Generator g = Generator(64, 7, 15, 3, 1368057209);
    std::cout << g.generate() << std::endl;
    std::cout << g << std::endl;
    return 0;
}
