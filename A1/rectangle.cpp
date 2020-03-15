#include "rectangle.hpp"

#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t &position, double width, double height) :
  position_(position),
  width_(width),
  height_(height)
{
  assert((width_ > 0) && (height_ > 0));
}

double Rectangle::getArea() const
{
  return (height_ * width_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, position_};
}

void Rectangle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void Rectangle::move(const point_t &param)
{
  position_ = param;
}

void Rectangle::printInfo() const
{
  rectangle_t info = getFrameRect();
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame rectangle: (" << info.pos.x << ", " << info.pos.y << ")\n";
  std::cout << "Frame width = " << info.width <<", frame height = " << info.height << "\n\n";
}

