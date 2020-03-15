#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>

class Shape 
{
public:
  struct point_t
  {
    int x;
    int y;
  };
  
  explicit Shape(const point_t &);
  virtual ~Shape() = default;
  
  bool isMoreLeft(const Shape &) const;
  bool isUpper(const Shape &) const;

  virtual void draw(std::ostream &) const = 0;

protected:
  point_t center_;
};

#endif

