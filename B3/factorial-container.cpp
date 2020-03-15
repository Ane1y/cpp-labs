#include "factorial-container.hpp"

const size_t MAX_SIZE = 11;
const size_t MIN_SIZE = 1;

FactorialContainer::FactorialIterator::FactorialIterator() :
  value_(1),
  index_(1)
{}

FactorialContainer::FactorialIterator::FactorialIterator(size_t index)
{
  if (index < MIN_SIZE || index > MAX_SIZE)
  {
    throw std::invalid_argument("You've just sent to constuctor the wrong index!\n");
  }
  value_ = count(index);
  index_ = index;
}

unsigned long long& FactorialContainer::FactorialIterator::operator *()
{
  return value_;
}

unsigned long long* FactorialContainer::FactorialIterator::operator ->()
{
  return &value_;
}

FactorialContainer::FactorialIterator& FactorialContainer::FactorialIterator::operator ++()
{
  index_++;
  value_ *= index_;

  return *this;
}

FactorialContainer::FactorialIterator& FactorialContainer::FactorialIterator::operator --()
{
  if (index_ > 1)
  {
    value_ /= index_;
    index_--;
  }

  return *this;
}

FactorialContainer::FactorialIterator FactorialContainer::FactorialIterator::operator ++(int)
{
  FactorialIterator temp = *this;
  ++(*this);

  return temp;
}

FactorialContainer::FactorialIterator FactorialContainer::FactorialIterator::operator --(int)
{
  FactorialIterator temp = *this;
  --(*this);

  return temp;
}

bool FactorialContainer::FactorialIterator::operator ==(const FactorialIterator& rhs) const
{
  return ((value_ == rhs.value_) && (index_ == rhs.index_));
}

bool FactorialContainer::FactorialIterator::operator !=(const FactorialIterator& rhs) const
{
  return !(*this == rhs);
}

unsigned long long FactorialContainer::FactorialIterator::count(size_t index) const
{
  if (index <= 1)
  {
    return 1;
  }
  else
  {
    return index * count(index - 1);
  }
}

FactorialContainer::FactorialIterator FactorialContainer::begin()
{
  return FactorialIterator(1);
}

FactorialContainer::FactorialIterator FactorialContainer::end()
{
  return FactorialIterator(MAX_SIZE);
}

