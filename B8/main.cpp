#include <iostream>

void task1(const size_t);

int main(int argc, char * argv[])
{
  size_t lineWidth = 40;
  if ((argc != 1) && (argc != 3))
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  
  try
  {
    if (argc == 3)
    {
      std::string lineWidthArgument = argv[1];
      
      if (lineWidthArgument != "--line-width")
      {
        std::cerr << "Invalid argument\n";
        return 1;
      }
      
      char *ptrEnd = nullptr;
      lineWidth = std::strtol(argv[2], &ptrEnd, 10);
      
      const size_t minLineWidth = 25;
      if (*ptrEnd || (lineWidth < minLineWidth))
      {
        std::cerr << "--line-width parameter must be a number and be more than 25\n";
        return 1;
      }
    }
    task1(lineWidth);
  }
  
  catch (const std::ios_base::failure &e)
{
  std::cerr << e.what() << "\n";
  return 1;
} catch (const std::exception &e)
{
  std::cerr << e.what() << "\n";
  return 2;
}

return 0;
}
