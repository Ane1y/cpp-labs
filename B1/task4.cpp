#include <random>
#include <vector>

#include "output.hpp"
#include "sort.hpp"

void fillRandom(double* array, size_t size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);
  for (size_t i = 0; i < size; ++i)
  {
    array[i] = dis(gen);
  }
}

void task4(const char* direction, size_t size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size must be greater than zero");
  }
  
  std::vector<double> vector(size);
  fillRandom(&vector[0], size);
  std::cout << vector;
  
  Direction dir = getDirection(direction);
  selectionSort<BracketAccess>(vector, dir);
  std::cout << vector;
}
