#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

const size_t initialCapacity = 10;

void task2(const char* file)
{
  std::ifstream inputFile(file);
 
  if (!inputFile)
  {
    throw std::runtime_error("Failed to open file.");
  }

  size_t capacity = initialCapacity;
  size_t size = 0;
  
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(malloc(capacity)), &free);
  if (!array)
  {
    throw std::runtime_error("Failed to allocate space.");
  }
  
  while (inputFile)
  {
    inputFile.read(&array[size], capacity - size);
    size += inputFile.gcount();

    if (size == capacity)
    {
      capacity *= 2;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char*>(realloc(array.get(), capacity)), &free);

      if (temp)
      {
        array.release();
        std::swap(array, temp);
      }
      else
      {
        throw std::runtime_error("Failed to allocate memory.");
      }
    }
  }
    


  if (!inputFile.eof() && !inputFile.fail()) {
    throw std::ios_base::failure("Reading from file failed.");
  }
  
  inputFile.close();
  
  std::vector<char> vector(&array[0], &array[size]);
  for(const auto& i: vector)
  {
    std::cout << i;
  }

}
