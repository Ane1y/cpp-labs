#include "sort.hpp"

#include <cstring>
#include <stdexcept>

Direction getDirection(const char* direction)
{
  if (std::strcmp(direction, "ascending") == 0)
  {
    return Direction::ascending;
  }

  if (std::strcmp(direction, "descending") == 0)
  {
    return Direction::descending;
  }

  throw std::invalid_argument("Incorrect sorting direction.");
}
