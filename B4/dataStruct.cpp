#include "dataStruct.hpp"

DataStruct read(std::istream& input)
{
  int keys[2] = {0};
  std::string str;
  for (int &key : keys)
  {
    input >> key;
    if (input.eof() || std::abs(key) > 5)
    {
      throw std::invalid_argument("Key must be in [-5; 5].\n");
    }

    std::getline(input, str, ',');
    if (input.eof() || !str.empty())
    {
      throw std::invalid_argument("Invalid key.\n");
    }
  }

  while (input.peek() == ' ')
  {
    input.get();
  }

  std::getline(input, str);
  if (str.empty())
  {
    throw std::invalid_argument("String is empty.\n");
  }

  return {keys[0], keys[1], str};
}

void print(const DataStruct& data)
{
  std::cout << data.key1 << ',' << data.key2 << ',' << data.str << std::endl;
}

void sort(std::vector<DataStruct> &vector)
{
  std::sort(vector.begin(), vector.end(), compare());
}
