#ifndef INTSTATISTICS_HPP
#define INTSTATISTICS_HPP

class IntStatistics
{
public:
  IntStatistics();

  void operator()(const int &number);
  void printStatistics();

private:
  int max_;
  int min_;
  double average_;
  int positiveCount_;
  int negativeCount_;
  long long int sumOdd_;
  long long int sumEven_;
  bool equalFirstLast_;
  
  int total_;
  int first_;
  
  bool empty_;
};

#endif
