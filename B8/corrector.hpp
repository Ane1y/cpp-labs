#ifndef PRINTOUTPUT_HPP
#define PRINTOUTPUT_HPP

#include <iostream>

#include "token.hpp"

class Corrector
{
public:
  Corrector(std::ostream &, token_list &);
  void print(size_t);
  
private:
  std::ostream & out_;
  token_list &list_;
  
  int dashAndPunctuationPrint(token_list &);
  void printLine(const token_list &);
  bool isValid();
  
};

#endif
