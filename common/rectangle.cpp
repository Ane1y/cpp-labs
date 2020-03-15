#include "rectangle.hpp"

#include <iostream>
#include <cmath>

dusaeva::Rectangle::Rectangle(const point_t &center, double width, double height) :
  center_(center),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if((height_ <= 0) || (width_ <= 0))
  {
    throw std::invalid_argument("Width and height must be greater than zero!");
  }
}

double dusaeva::Rectangle::getArea() const
{
  return (height_ * width_);
}

dusaeva::rectangle_t dusaeva::Rectangle::getFrameRect() const
{
  double radAngle = M_PI * angle_ / 180;
  
  return rectangle_t{width_ * fabs(cos(radAngle)) + height_ * fabs(sin(radAngle)),
      width_ * fabs(sin(radAngle)) + height_ * fabs(cos(radAngle)),
      center_};
}

void dusaeva::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void dusaeva::Rectangle::move(const point_t &newCenter)
{
  center_ = newCenter;
}

void dusaeva::Rectangle::printInfo() const
{
  rectangle_t info = getFrameRect();
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame rectangle: (" << info.pos.x << ", " << info.pos.y << ")\n";
  std::cout << "Frame width = " << info.width <<", frame height = " << info.height << "\n\n";
}

void dusaeva::Rectangle::scale(double scale)
{
  if (scale <= 0)
  {
    throw std::invalid_argument("Scale factor must be greater than zero!");
  }
  height_ *= scale;
  width_ *= scale;
}

void dusaeva::Rectangle::rotate(double angle)
{
  angle_ += angle;
}
