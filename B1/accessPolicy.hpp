#ifndef ACCESSPOLYCY_HPP
#define ACCESSPOLYCY_HPP

#include <iterator>

template <typename T>
struct BracketAccess
{
  static size_t begin(const T&)
  {
    return 0;
  }

  static size_t end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference element(T& collection, size_t i)
  {
    return collection[i];
  }

  static size_t next(size_t i)
  {
    return i + 1;
  }
};

template <typename T>
struct AtAccess
{
  static size_t begin(const T&)
  {
    return 0;
  }

  static size_t end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference element(T& collection, size_t i)
  {
    return collection.at(i);
  }

  static size_t next(size_t i)
  {
    return i + 1;
  }
};

template <typename T>
struct IteratorAccess
{
  typedef typename T::iterator iteratorType;

  static iteratorType begin(T& collection)
  {
    return collection.begin();
  }

  static iteratorType end(T& collection)
  {
    return collection.end();
  }

  static typename T::reference element(T&, iteratorType& iterator)
  {
    return *iterator;
  }

  static iteratorType next(iteratorType& iterator)
  {
    return std::next(iterator);
  }
};

#endif
