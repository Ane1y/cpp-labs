#include <iostream>
#include <vector>
#include <algorithm>

#include "intstatistics.hpp"

void task1()
{
  std::vector<int> v;
  int number = 0;

  while (std::cin >> number, !std::cin.eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Failed input. \n");
    }

    v.push_back(number);
  }

  IntStatistics stat;
  stat = std::for_each(v.begin(), v.end(), IntStatistics());
  stat.printStatistics();
}
