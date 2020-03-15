#include <forward_list>
#include <vector>

#include "output.hpp"
#include "sort.hpp"

void task1(const char* direction)
{
  std::vector<int> vectorBracket;
  auto sortDirection = getDirection(direction);
  int inputNum = 0;
  
  while (std::cin >> inputNum)
  {
    vectorBracket.push_back(inputNum);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("An error was occurred while reading data.");
  }

  if (vectorBracket.empty())
  {
    return;
  }

  std::vector<int> vectorAt = vectorBracket;
  std::forward_list<int> list(vectorBracket.begin(), vectorBracket.end());
  
  selectionSort<BracketAccess>(vectorBracket, sortDirection);
  selectionSort<AtAccess>(vectorAt, sortDirection);
  selectionSort<IteratorAccess>(list, sortDirection);
  
  std::cout << vectorBracket << vectorAt << list;
}
