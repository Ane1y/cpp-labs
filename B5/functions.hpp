#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <set>
#include "shape.hpp"

void parse(std::set<std::string> &container);
void print(const std::set<std::string> &container);

void readShape(std::vector<Shape>& vector, std::string& line);
Shape readPoints(std::string& line, size_t vertices);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isLess(const Shape& shape1, const Shape& shape2);
int getLength(const point_t&, const point_t&);

#endif
