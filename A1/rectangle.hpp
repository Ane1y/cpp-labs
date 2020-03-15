#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &, double, double);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double, double) override;
  void move(const point_t &) override;
  void printInfo() const override;

private:
  point_t position_;
  double width_;
  double height_;
};

#endif
