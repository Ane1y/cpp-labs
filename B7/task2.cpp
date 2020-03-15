#include <algorithm>
#include <sstream>
#include <vector>

#include "shapes.hpp"

typedef std::shared_ptr<Shape> shape_ptr;

std::vector<shape_ptr> createVector();

void task2()
{
  std::vector<shape_ptr> v = createVector();
  
  std::cout << "Original:\n";
  std::for_each(v.begin(), v.end(), [](const shape_ptr shape) { shape->draw(std::cout); });
  
  std::sort(v.begin(), v.end(), [](const shape_ptr &shape1, const shape_ptr &shape2)
  { return shape1->isMoreLeft(*shape2); });
  std::cout << "Left-Right:\n";
  std::for_each(v.begin(), v.end(), [](const shape_ptr shape)
  { shape->draw(std::cout); });
  
  std::cout << "Right-Left:\n";
  std::for_each(v.rbegin(), v.rend(), [](const shape_ptr shape) { shape->draw(std::cout); });
  
  std::sort(v.begin(), v.end(), [](const shape_ptr shape1, const shape_ptr shape2)
  { return (shape1->isUpper(*shape2)); });
  std::cout << "Top-Bottom:\n";
  std::for_each(v.begin(), v.end(), [](const shape_ptr shape) { shape->draw(std::cout); });

  std::cout << "Bottom-Top:\n";
  std::for_each(v.rbegin(), v.rend(), [](const shape_ptr shape) { shape->draw(std::cout); });
}

std::vector<shape_ptr> createVector()
{
  std::string str;
  std::vector<shape_ptr> v;
  
  while (std::getline(std::cin, str))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("Error while reading data");
    }
  
    str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return std::isspace(c); }), str.end());
    
    if (str.empty())
    {
      continue;
    }
    auto pos = str.find_first_of('(');
    
    if (pos == std::string::npos)
    {
      throw std::invalid_argument("Incorrect input. No open parentheses");
    }
    
    std::string name = str.substr(0, pos);
    str.erase(0, pos + 1);
    
    pos = str.find_first_of(';');
    
    if (pos == std::string::npos)
    {
      throw std::invalid_argument("Incorrect input. No semicolon");
    }
    
    Shape::point_t center{0, 0};
    char *end = nullptr;
    center.x = std::strtoll(str.c_str(), &end, 10);
  
    str.erase(0, pos + 1);
    
    pos = str.find_first_of(')');
    if (pos == std::string::npos)
    {
      throw std::invalid_argument("Incorrect input. No close parentheses");
    }
    center.y = std::strtoll(str.c_str(), &end, 10);
    
    if (name == "TRIANGLE")
    {
      v.emplace_back(std::make_shared<Triangle>(Triangle(center)));
    } else if (name == "SQUARE") {
      v.emplace_back(std::make_shared<Square>(Square(center)));
    } else if (name == "CIRCLE") {
      v.emplace_back(std::make_shared<Circle>(Circle(center)));
    } else {
      throw std::invalid_argument("Invalid shape name");
    }
  }
  return v;
}
