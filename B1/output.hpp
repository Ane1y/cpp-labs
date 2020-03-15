#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

template <typename T, typename = typename T::const_iterator>
std::ostream& operator<<(std::ostream& out, const T& container)
{
  for (auto& element: container)
  {
    out << element << " ";
  }
  out << "\n";
  return out;
}

#endif
