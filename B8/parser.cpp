#include "parser.hpp"

Parser::Parser(std::istream &input) :
        input_(input)
{}

void Parser::parseInput()
{
  while (input_)
  {
    char ch = input_.get();
    while (std::isspace(ch, std::locale()))
    {
      ch = input_.get();
    }
  
    if (isalpha(ch, std::locale()))
    {
      input_.unget();
      readWord();
    } else if (ch == '-')
    {
      if (input_.peek() == '-')
      {
        input_.unget();
        readDash();
      } else {
        input_.unget();
        readNumber();
      }
    } else if ((ch == '+') || (isdigit(ch, std::locale()))) {
      input_.unget();
      readNumber();
    } else if (ispunct(ch, std::locale())) {
      token_t str{"", tokenType::PUNCTUATION};
      str.value.push_back(ch);
      text_.push_back(str);
    }
  }
}

void Parser::readWord()
{
  token_t str{"", tokenType::WORD};
  do {
    char ch = input_.get();
  
    str.value.push_back(ch);
    if (ch == '-' && input_.peek() == '-')
    {
      str.value.pop_back();
      input_.unget();
      break;
    }
  } while ((std::isalpha<char>(input_.peek(), std::locale())) || (input_.peek() == '-'));
  text_.push_back(str);
}

void Parser::readNumber()
{
  token_t str{"", tokenType::NUMBER};
  
  char decPoint = std::use_facet<std::numpunct<char>>(std::locale()).decimal_point();
  bool decPointFlag = false;
  do {
    char ch = input_.get();
    if (ch == decPoint)
    {
      if (decPointFlag)
      {
        input_.unget();
        break;
      }
      decPointFlag = true;
    }
    str.value.push_back(ch);
  } while ((std::isdigit<char>(input_.peek(), std::locale()) || (input_.peek() == decPoint)));
  
  text_.push_back(str);
}

void Parser::readDash()
{
  token_t str{"", tokenType::DASH};
  while (input_.peek() == '-')
  {
    char ch = input_.get();
    str.value.push_back(ch);
  }
  text_.push_back(str);
}

token_list::iterator Parser::begin()
{
  return text_.begin();
}

token_list::iterator Parser::end()
{
  return text_.end();
}
