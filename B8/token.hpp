#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <list>

constexpr size_t MaxWordLength = 20;
constexpr size_t DashLength = 3;
constexpr size_t SpaceLength = 1;
constexpr size_t PunctLength = 1;

enum tokenType
{
  WORD,
  NUMBER,
  PUNCTUATION,
  DASH,
  WS
};

struct token_t
{
  std::string value;
  tokenType type;
};

typedef std::list<token_t> token_list;

#endif
