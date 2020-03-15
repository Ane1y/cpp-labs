#include <set>
#include <iostream>
#include "functions.hpp"

void task1()
{
  std::set<std::string> words;
  parse(words);
  print(words);
}
