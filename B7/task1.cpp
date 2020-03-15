#include <algorithm>
#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>

void task1()
{
  std::vector<double> vector{std::istream_iterator<double>(std::cin), std::istream_iterator<double>()};
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Invalid input!");
  }
  if (vector.empty())
  {
    return;
  }
  std::transform(vector.begin(), vector.end(), vector.begin(),
                 std::bind2nd(std::multiplies<double>(), M_PI));
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(std::cout, "\n"));
}
