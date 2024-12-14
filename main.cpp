
#include "Generator.h"

int main()
{
  Generator g = Generator(64, 3, 7, 3, 1755333420);
  std::cout << g.generate() << std::endl;
  std::cout << g << std::endl;
  return 0;
}