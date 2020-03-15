#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &);
  void draw(std::ostream &) const override;
};

class Square : public Shape
{
public:
  Square(const point_t &);
  void draw(std::ostream&) const override;
};

class Triangle : public Shape
{
public:
  Triangle(const point_t &);
  void draw(std::ostream &) const override;
};

#endif
