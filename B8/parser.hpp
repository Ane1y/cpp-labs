#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <locale>
#include <memory>

#include "token.hpp"


class Parser
{
public:
  
  Parser(std::istream &);

  void parseInput();

  token_list::iterator begin();
  token_list::iterator end();

private:
  std::istream &input_;
  
  token_list text_;
  
  void readWord();
  void readNumber();
  void readDash();
  
};


#endif
