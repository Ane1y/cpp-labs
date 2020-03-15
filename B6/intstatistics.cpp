#include <iostream>

#include "intstatistics.hpp"

IntStatistics::IntStatistics() :
  max_(0),
  min_(0),
  average_(0),
  positiveCount_(0),
  negativeCount_(0),
  sumOdd_(0),
  sumEven_(0),
  equalFirstLast_(false),
  total_(0),
  first_(0),
  empty_(true)
  {}

void IntStatistics::operator()(const int &number)
{
  if (empty_)
  {
    max_ = number;
    min_ = number;
    first_ = number;
    empty_ = false;
  }

  max_ = std::max(max_, number);
  min_ = std::min(min_, number);

  if (number > 0)
  {
    positiveCount_++;
  } 
  else if (number < 0)
  {
    negativeCount_++;
  }
  
  total_++;
  (number % 2 == 0) ? (sumEven_ +=  number) : (sumOdd_ += number);
  average_ = (sumOdd_+ sumEven_) / static_cast<double>(total_);
  equalFirstLast_ = (first_ == number);

}

void IntStatistics::printStatistics()
{
  if (empty_)
  {
    std::cout << "No Data" << std::endl;
    return;
  }

  std::cout << "Max: " << max_ << std::endl;
  std::cout << "Min: " << min_ << std::endl;
  std::cout << "Mean: " << average_ << std::endl;
  std::cout << "Positive: " << positiveCount_ << std::endl;
  std::cout << "Negative: " << negativeCount_ << std::endl;
  std::cout << "Odd Sum: " << sumOdd_ << std::endl;
  std::cout << "Even Sum: " << sumEven_ << std::endl;
  std::cout << "First/Last Equal: " << (equalFirstLast_ ? "yes" : "no") << std::endl;
}
