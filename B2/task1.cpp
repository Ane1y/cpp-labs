#include <sstream>
#include <iostream>

#include "commands.hpp"

void task1()
{
  QueueWithPriority<std::string> queue;
  std::string line;

  while (getline(std::cin, line))
  {
    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::ios_base::failure("Failed while reading data");
    }

    Commands::parseCommand(line)(queue, std::cout);
  }
  
}
