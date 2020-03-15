#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include "queue-with-priority.hpp"

class Commands
{
public:
  using stringQueue = QueueWithPriority<std::string>;
  using commandExecution = std::function<void(stringQueue &, std::ostream &)>;

  static commandExecution parseCommand(std::string & args);

private:
  static const commandExecution invalidCommandWarning;
  
  static void skipSpaces(std::string &);
  static std::string divideWords(std::string &);

  static commandExecution parseAdd(std::string &);
  static commandExecution parseGet(std::string &);
  static commandExecution parseAccelerate(std::string &);
  
};

#endif
