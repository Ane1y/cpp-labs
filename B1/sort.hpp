#ifndef SORT_HPP
#define SORT_HPP

#include <functional>

#include "accessPolicy.hpp"

enum class Direction
{
  ascending,
  descending
};

Direction getDirection(const char* direction);

template <template <class T> class Access, typename T>
void selectionSort(T& collection, Direction direction)
{
  using value_type = typename T::value_type;

  std::function<bool(value_type, value_type)> compare = (direction == Direction::ascending)
      ? std::function<bool(value_type, value_type)>(std::less<value_type>())
      : std::function<bool(value_type, value_type)>(std::greater<value_type>());

  const auto begin = Access<T>::begin(collection);
  const auto end = Access<T>::end(collection);
  
  
  for (auto i = begin; i != end; i++)
  {
    for (auto j = begin; j != end; j++)
    {
      typename T::value_type& a = Access<T>::element(collection, i);
      typename T::value_type& b = Access<T>::element(collection, j);
      
      if (compare(a, b)) {
        std::swap(a, b);
      }
    }
  }
}

#endif
