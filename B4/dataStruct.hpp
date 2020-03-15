#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

struct compare
{
  bool operator()(const DataStruct &data1, const DataStruct &data2)
  {
    if (data1.key1 < data2.key1)
    {
      return true;
    }

    if (data1.key1 == data2.key1)
    {
      if (data1.key2 < data2.key2)
      {
        return true;
      }

      if (data1.key2 == data2.key2)
      {
        return data1.str.length() < data2.str.length();
      }
    }
    return false;
  }
};

DataStruct read(std::istream &input);

void print(const DataStruct &data);
void sort(std::vector<DataStruct> &vector);

#endif
