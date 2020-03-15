#include <iostream>
#include <list>

void task2()
{
  const size_t maxSize = 20;
  const int minNum = 1;
  const int maxNum = 20;

  std::list<int> list;
  size_t size = 0;
  int num = 0;

  while(std::cin >> num)
  {
    if ((num > maxNum) || (num < minNum))
    {
      throw std::ios_base::failure("Number must be in [1, 20] interval");
    }
    if (size >= maxSize)
    {
      throw std::ios_base::failure("List overflow. Max size is 20.");
    }
    
    list.push_back(num);
    size++;
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Failed to read data.");
  }

  if (list.empty())
  {
    std::cout << "\n";
    return;
  }

  auto begin = list.begin();
  auto end = list.end();

  while(begin != end)
  {
    std::cout << *(begin++);

    if (begin == end)
    {
      break;
    }

    std::cout << " " << *(--end);

    if (begin != end)
    {
      std::cout << " ";
    }
  }

  std::cout << "\n";
}
