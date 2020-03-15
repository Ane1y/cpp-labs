#include "corrector.hpp"

Corrector::Corrector(std::ostream &out, token_list &list) :
  out_(out),
  list_(list)
{
  if (!isValid())
  {
    throw std::ios_base::failure("Incorrect input");
  }
}

void Corrector::print(size_t lineWidth)
{
  size_t currentWidth = 0;
  token_list line;
  for (auto &el : list_)
  {
    switch(el.type)
    {
      case tokenType::PUNCTUATION:
        if (currentWidth + PunctLength > lineWidth)
        {
          currentWidth = dashAndPunctuationPrint(line);
        }
        line.push_back(el);
        currentWidth += (el).value.size();
        break;
      case tokenType::DASH:
        if (currentWidth + DashLength + SpaceLength > lineWidth)
        {
          currentWidth = dashAndPunctuationPrint(line);
        }
        line.push_back(token_t{" ", tokenType::WS});
        line.push_back(el);
        currentWidth += el.value.size() + 1;
        break;
      case tokenType::WORD:
      case tokenType::NUMBER:
        if (currentWidth + el.value.size() + SpaceLength > lineWidth)
        {
          printLine(line);
          line.clear();
          currentWidth = 0;
        } else if (!line.empty())
        {
          line.push_back(token_t{" ", tokenType::WS});
          currentWidth++;
        }
        line.push_back(el);
        currentWidth += el.value.size();
        break;
      case tokenType::WS:
        break;
    }
    
  }
  if (!line.empty())
  {
    printLine(line);
  }
}

void Corrector::printLine(const token_list &line)
{
  for (const auto &el : line)
  {
    out_ << el.value;
  }
  out_ << "\n";
}

int Corrector::dashAndPunctuationPrint(token_list &list)
{
  size_t width = 0;
  token_list line;
  while (!list.empty())
  {
    line.push_front(list.back());
    width += list.back().value.size();
    list.pop_back();
    if (line.front().type == tokenType::WORD || line.front().type == tokenType::NUMBER)
    {
      break;
    }
  }
  printLine(list);
  list = line;
  return width;
}

bool Corrector::isValid()
{
  if (!list_.empty() && (list_.front().type != tokenType::WORD) && (list_.front().type != tokenType::NUMBER))
  {
    return false;
  }
  for (auto el = list_.begin(); el != list_.end(); el++)
  {
    switch(el->type)
    {
      case tokenType::WORD:
      case tokenType::NUMBER:
        if (el->value.size() > 20)
        {
          return false;
        }
        break;
      case tokenType::DASH:
        if (el->value.size() != 3)
        {
          return false;
        }
        if (el != list_.begin()) {
          const token_t &prev = *std::prev(el);
          if ((prev.type == tokenType::DASH) || ((prev.type == tokenType::PUNCTUATION) && (prev.value != ",")))
          {
            return false;
          }
        }
        break;
      case tokenType::PUNCTUATION:
        if (el != list_.begin())
        {
          const token_t &prev = *std::prev(el);
          if ((prev.type == tokenType::DASH) || (prev.type == tokenType::PUNCTUATION))
          {
            return false;
          }
        }
        break;
      case tokenType::WS:
        break;
    }
  }
  return true;
}
