#include "triangle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Triangle::Triangle(const point_t &pointA, const point_t &pointB, const point_t &pointC) :
  pointA_(pointA),
  pointB_(pointB),
  pointC_(pointC),
  center_{(pointA_.x + pointB_.x + pointC_.x) / 3, (pointA_.y + pointB_.y + pointC_.y) / 3}
{
  assert(getArea() > 0.0);
}

double Triangle::getArea() const
{
  double square = fabs(((pointA_.x - pointC_.x) * (pointB_.y - pointC_.y)
      - (pointA_.y - pointC_.y) * (pointB_.x - pointC_.x)) / 2);

  return square;
}

rectangle_t Triangle::getFrameRect() const
{
  point_t minPoint{std::min(pointA_.x, std::min(pointB_.x, pointC_.x)),
      std::min(pointA_.y, std::min(pointB_.y, pointC_.y))};

  point_t maxPoint{std::max(pointA_.x, std::max(pointB_.x, pointC_.x)),
      std::max(pointA_.y, std::max(pointB_.y, pointC_.y))};

  double width = maxPoint.x - minPoint.x;
  double height = maxPoint.y - minPoint.y;

  point_t frameCenter{minPoint.x + width / 2, minPoint.y + height / 2};

  return rectangle_t{width, height, frameCenter};
}

void Triangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;

  pointA_.x += dx;
  pointB_.x += dx;
  pointC_.x += dx;

  pointA_.y += dy;
  pointB_.y += dy;
  pointC_.y += dy;
}

void Triangle::move(const point_t &param)
{
  double dx = param.x - center_.x;
  double dy = param.y - center_.y;

  move(dx, dy);
}

void Triangle::printInfo() const
{
  rectangle_t info = getFrameRect();

  std::cout << "Center: (" << center_.x << ", " << center_.y << ")\n";
  std::cout << "Area = " << getArea() << "\n";
  std::cout << "Central coordinates of frame: (" << info.pos.x << ", " << info.pos.y << ")\n";
  std::cout << "Frame width = " << info.width <<", frame height = " << info.height << "\n\n";
}
