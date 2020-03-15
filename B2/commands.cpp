#include "commands.hpp"

#include <algorithm>
#include <sstream>

const commands::commandExecution commands::invalidCommandWarning = [](stringQueue &, std::ostream &out) { out << "<INVALID COMMAND>\n"; };

commands::commandExecution commands::parseCommand(std::string &args)
{
  using parserExecution = std::function<commands::commandExecution(std::string &)>;

  struct parsers_t
  {
    const char *name;
    parserExecution execution;
  };

  static const parsers_t parsers[]
  {
    { "add", &parseAdd },
    { "get", &parseGet },
    { "accelerate", &parseAccelerate }
  };

  skipSpaces(args);
  
  std::string parsedWord = divideWords(args);

  auto parser = std::find_if(parsers, std::end(parsers),
      [&](const parsers_t &parser) { return parser.name == parsedWord; });

  if (parser == std::end(parsers))
  {
    return invalidCommandWarning;
  } else {
    return parser->execution(args);
  }
}

void commands::skipSpaces(std::string &str)
{
  size_t num = 0;
  while (isblank(str[num]))
  {
    num++;
  }

  str.erase(0, num);
}

std::string commands::divideWords(std::string &str)
{
  if (str.empty())
  {
    return "";
  }

  size_t wordLength = 0;

  while (!isblank(str[wordLength]))
  {
    wordLength++;
    if (wordLength == str.length())
    {
      break;
    }
  }

  std::string word = str.substr(0, wordLength);
  str.erase(0, wordLength);

  return word;
}

commands::commandExecution commands::parseAdd(std::string &args)
{
  using queuePriorities = stringQueue::ElementPriority;

  struct ElementPriority
  {
    const char *name;
    queuePriorities priority;
  };

  static const ElementPriority priorities[]
  {
    { "low", queuePriorities::LOW },
    { "normal", queuePriorities::NORMAL },
    { "high", queuePriorities::HIGH }
  };

  skipSpaces(args);
  std::string currentPriority = divideWords(args);

  auto priority = std::find_if(priorities, std::end(priorities),
      [&](const ElementPriority &priority) { return priority.name == currentPriority; });

  if (priority == std::end(priorities))
  {
    return invalidCommandWarning;
  }

  skipSpaces(args);
  std::string data = args;

  if (data.empty())
  {
    return invalidCommandWarning;
  }

  return [=](stringQueue &queue, std::ostream &) { queue.putElement(data, priority->priority); };
}

commands::commandExecution commands::parseGet(std::string & args)
{
  skipSpaces(args);
  std::string line = args;

  if (!line.empty())
  {
    return invalidCommandWarning;
  }

  return [](stringQueue & queue, std::ostream & out)
  {
      if (queue.empty())
      {
        out << "<EMPTY>\n";
      } else {
        queue.getElement([&](std::string element) { out << element << "\n"; });
      }
  };
}

commands::commandExecution commands::parseAccelerate(std::string & args)
{
  skipSpaces(args);
  std::string line = args;

  if (!line.empty())
  {
    return invalidCommandWarning;
  }

  return [](stringQueue & q, std::ostream & out)
  {
      if (q.empty())
      {
        out << "<EMPTY>\n";
      } else {
        q.accelerate();
      }
  };
}
