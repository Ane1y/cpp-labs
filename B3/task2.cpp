#include <algorithm>
#include <iostream>
#include "factorial-container.hpp"

void task2()
{
  FactorialContainer factorial;

  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
