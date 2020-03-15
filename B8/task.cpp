#include "corrector.hpp"
#include "parser.hpp"

void task1(const size_t lineWidth)
{
  Parser parser(std::cin);

  parser.parseInput();
    
  token_list tokenList(parser.begin(), parser.end());
  Corrector output(std::cout, tokenList);
  output.print(lineWidth);
}
