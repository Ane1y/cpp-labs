#include <iostream>
#include <sstream>
#include <algorithm>

#include "dataStruct.hpp"

void task1()
{
  std::vector<DataStruct> vector;
  std::string str;
  
  while (std::getline(std::cin, str))
  {
    if (!std::cin && !std::cin.eof())
    {
      throw std::ios_base::failure("Error input data. \n");
    }

    std::istringstream stream(str);
    vector.push_back(read(stream));
  }
  sort(vector);
  std::for_each(vector.begin(), vector.end(), print);
}
