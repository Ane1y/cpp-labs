#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"
#include "composite-shape.hpp"



int main()
{
  dusaeva::Shape::ptr_type circlePtr = std::make_shared<dusaeva::Circle>(dusaeva::point_t{1, 2}, 4);
  dusaeva::Shape::ptr_type rectanglePtr = std::make_shared<dusaeva::Rectangle>(dusaeva::point_t{1.0, 2.0}, 4.0, 5.0);
  dusaeva::Shape::ptr_type trianglePtr = std::make_shared<dusaeva::Triangle>(dusaeva::point_t{4.0, 10.0},
      dusaeva::point_t{15.0, 6.0}, dusaeva::point_t{1.0, 1.0});
  dusaeva::point_t *points = new dusaeva::point_t[3]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}};
  dusaeva::Shape::ptr_type polygonPtr = std::make_shared<dusaeva::Polygon>(3, points);
  delete[] points;

  dusaeva::CompositeShape compositeShape;

  compositeShape.add(circlePtr);
  compositeShape.add(rectanglePtr);
  compositeShape.add(trianglePtr);
  compositeShape.add(polygonPtr);
  
  std::cout << "Composite shape:\n";
  compositeShape.printInfo();
  
  compositeShape.move(5.0, 6.5);
  std::cout << "Shift move on (5, 6.5):\n";
  compositeShape.printInfo();
  
  compositeShape.move({1.0, 2.5});
  std::cout << "Move to point (1, 2.5):\n";
  compositeShape.printInfo();
  
  compositeShape.scale(3.5);
  std::cout << "Scale by 3.5:\n";
  compositeShape.printInfo();
  
  std::cout << "Delete circle and rectangle:\n";
  compositeShape.remove(1);
  compositeShape.remove(2);
  compositeShape.printInfo();
  
  size_t count = compositeShape.getCount();
  std::cout << "Count of shapes:" << count << std::endl;
  std::cout << "Get any shape and print its info:\n";
  compositeShape[1]->printInfo();//triangle info
  return 0;
}
