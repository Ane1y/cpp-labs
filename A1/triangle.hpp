#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &, const point_t &, const point_t &);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move (const point_t &) override;
  void move (double,  double) override;
  void printInfo() const override;
  
private:
  point_t pointA_;
  point_t pointB_;
  point_t pointC_;
  point_t center_;
};

#endif
