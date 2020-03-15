#include <iostream>
#include "shape.hpp"
#include "functions.hpp"
const size_t RECTANGLE_VERT = 4;

void parse(std::set<std::string> &container)
{
  std::string str;
  while (std::getline(std::cin, str))
  {

    while (str.find_first_of(" \n\t") == 0)
    {
      str.erase(0, 1);
    }

    while (!str.empty())
    {
      size_t position = str.find_first_of(" \n\t");

      std::string word;
      word = str.substr(0, position);
      container.emplace(word);

      str.erase(0, position);
      while (str.find_first_of(" \n\t") == 0) 
      {
        str.erase(0, 1);
      }
    }
  }
}

void print(const std::set<std::string> &container)
{
  for (const auto &v : container)
  {
    std::cout << v << std::endl;
  }
}

void readShape(std::vector<Shape> &vector, std::string &str)
{
  while (std::getline(std::cin, str))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Error occured while reading data \n");
    }

    while (str.find_first_of(" \t") == 0)
    {
      str.erase(0, 1);
    }

    if (str.empty())
    {
      continue;
    }

    size_t position = str.find_first_of('(');
    if (position == std::string::npos)
    {
      throw std::invalid_argument("Invalid shape. \n");
    }

    size_t numberOfVert = std::stoi(str.substr(0, position));
    str.erase(0, position);
    if (numberOfVert < 1)
    {
      throw std::invalid_argument("Invalid number of vertices\n");
    }

    Shape shape = readPoints(str, numberOfVert);

    vector.push_back(shape);
  }
}

Shape readPoints(std::string &str, size_t vertices)
{
  Shape shape;
  size_t lBracket;
  size_t semicolon;
  size_t rBracket;

  for (size_t i = 0; i < vertices; i++)
  {
    if (str.empty())
    {
      throw std::invalid_argument("Invalid number of vertices. \n");
    }

    while (str.find_first_of(" \t") == 0)
    {
      str.erase(0, 1);
    }

    lBracket = str.find_first_of('(');
    semicolon = str.find_first_of(';');
    rBracket = str.find_first_of(')');

    if ((lBracket == std::string::npos) || (semicolon == std::string::npos) || (rBracket == std::string::npos))
    {
      throw std::invalid_argument("Invalid point declaration. \n");
    }

    point_t point
      {
        std::stoi(str.substr(lBracket + 1, semicolon - lBracket - 1)),
        std::stoi(str.substr(semicolon + 1, rBracket - semicolon - 1))
      };

    str.erase(0, rBracket + 1);

    shape.push_back(point);
  }

  while (str.find_first_of(" \t") == 0)
  {
    str.erase(0, 1);
  }

  if (!str.empty())
  {
    throw std::invalid_argument("Too many points. \n");
  }

  return shape;
}

bool isRectangle(const Shape &shape)
{
  int diag1 = getLength(shape[0], shape[2]);
  int diag2 = getLength(shape[1], shape[3]);

  int vert1 = getLength(shape[0], shape[1]);
  int vert2 = getLength(shape[1], shape[2]);
  int vert3 = getLength(shape[2], shape[3]);
  int vert4 = getLength(shape[3], shape[0]);

  return ((vert1 == vert3) && (vert2 == vert4) && (diag1 == diag2));
}

bool isSquare(const Shape &shape)
{
  if (isRectangle(shape))
  {
    int side1 = getLength(shape[0], shape[1]);
    int side2 = getLength(shape[1], shape[2]);

    if (side1 == side2)
    {
      return true;
    }
  }
  return false;
}


bool isLess(const Shape& shape1, const Shape& shape2)
{
  if (shape1.size() < shape2.size())
  {
    return true;
  }
  if ((shape1.size() == RECTANGLE_VERT) && (shape2.size() == RECTANGLE_VERT))
  {
    if (isSquare(shape1))
    {
      if (isSquare(shape2))
      {
        return (shape1[0].x < shape2[0].x);
      }
      return true;
    }
  }
  return false;
}

int getLength(const point_t &point1, const point_t &point2)
{
  return (point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}
