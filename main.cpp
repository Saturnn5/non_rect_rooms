
#include "Generator.h"

int main()
{
  Generator g = Generator(64, 9, 13, 3);
  std::cout << g.generate() << std::endl;
  std::cout << g << std::endl;
  return 0;
}