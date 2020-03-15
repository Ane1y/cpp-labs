#include <iostream>

void task1();

int main()
{
  try
  {
    task1();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
