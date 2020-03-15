#ifndef QUEUEWITHPRIORITY_HPP
#define QUEUEWITHPRIORITY_HPP

#include <list>

template <typename T>
class QueueWithPriority
{
public:
  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  bool putElement(const T &element, ElementPriority priority);
  
  template <typename HandleType>
  bool getElement(HandleType handler);

  void accelerate();
  bool empty() const;
  void clear();

private:
  std::list<T> high_;
  std::list<T> normal_;
  std::list<T> low_;
};


template <typename T>
bool QueueWithPriority<T>::putElement(const T & element, ElementPriority priority)
{
  switch (priority)
  {
  case ElementPriority::HIGH:
    {
      high_.insert(high_.end(), element);
      return true;
    }
  case ElementPriority::NORMAL:
    {
      normal_.insert(normal_.end(), element);
      return true;
    }
  case ElementPriority::LOW:
    {
      low_.insert(low_.end(), element);
      return true;
    }
  default:
    {
      return false;
    }
  }
}

template <typename T>
template <typename HandleType>
bool QueueWithPriority<T>::getElement(HandleType handler)
{
  if (!high_.empty())
  {
    handler(high_.front());
    high_.pop_front();
    return true;
  }

  if (!normal_.empty())
  {
    handler(normal_.front());
    normal_.pop_front();
    return true;
  }

  if (!low_.empty()) {
    handler(low_.front());
    low_.pop_front();
    return true;
  }
  
  return false;
}

template <typename T>
void QueueWithPriority<T>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template <typename T>
bool QueueWithPriority<T>::empty() const
{
  return (high_.empty() && normal_.empty() && low_.empty());
}

template <typename T>
void QueueWithPriority<T>::clear()
{
  high_.clear();
  normal_.clear();
  low_.clear();
}

#endif
