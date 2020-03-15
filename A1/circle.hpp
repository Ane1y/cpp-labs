#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &, double);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double, double) override;
  void move(const point_t &) override;
  void printInfo() const override;

private:
  point_t position_;
  double radius_;
};

#endif
