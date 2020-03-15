#include <iostream>

void task1();
void task2();

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect number of parameters number! \n" << std::endl;
    return 1;
  }

  std::string taskNumber(argv[1]);

  try {
    if (taskNumber == "1")
    {
      task1();
    } else if (taskNumber == "2")
    {
      task2();
    } else {
      std::cerr << "Incorrect task number! \n" << std::endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
