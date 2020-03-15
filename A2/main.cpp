#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"

void modifyShape(dusaeva::Shape &shape, double dx, double dy, const dusaeva::point_t &dt, double scale)
{
  shape.printInfo();

  shape.move(dx, dy);
  std::cout << "Coordinate shift:\n";
  shape.printInfo();

  shape.move(dt);
  std::cout << "Point shift:\n";
  shape.printInfo();

  shape.scale(scale);
  std::cout << "Scale:\n";
  shape.printInfo();

}

int main()
{
  //Rectangle
  dusaeva::Rectangle objRectangle({5.0, 6.0}, 7.0, 1.0);
  dusaeva::Shape *shape = &objRectangle;

  std::cout << "\nRectangle:\n";
  modifyShape(*shape, 5.1, 6.2, {0.0, 3.0}, 2.0);

  //Circle
  dusaeva::Circle objCircle({1.0, 5.0}, 6.0);
  shape = &objCircle;

  std::cout << "\nCircle:\n";
  modifyShape(*shape, 1.0, 2.0, {7.8, -9.0}, 1.5);

  //Triangle
  dusaeva::Triangle objTriangle({4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0});
  shape = &objTriangle;

  std::cout << "\nTriangle:\n";
  modifyShape(*shape, 5.4, 7.6, {1.0, 3.0}, 2.0);

  //Polygon - triangle
  dusaeva::point_t *points = new dusaeva::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
  dusaeva::Polygon objPolygon{3, points};
  delete[] points;
  shape = &objPolygon;

  std::cout << "\nPolygon(triangle):\n";
  modifyShape(*shape, 1.02, 2.1, {6.0, 4.001}, 1.5);

 //Polygon
  dusaeva::point_t *points1 = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
  dusaeva::Polygon objPolygon2(4, points1);
  delete[] points1;
  shape = &objPolygon2;

  std::cout << "\n4-side polygon:\n";
  modifyShape(*shape, 1.0, 9.0, {3.2, 4.2}, 6.0);

  return 0;
}

