#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>

struct point_t
{
  int x, y;
};

using Shape = std::vector<point_t>;

#endif
