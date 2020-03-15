#ifndef PARTITION_HPP
#define PARTITION_HPP

#include "matrix.hpp"
#include "composite-shape.hpp"

namespace dusaeva
{
  bool intersect(const rectangle_t &lhs, const rectangle_t &rhs);
  dusaeva::Matrix partition(const dusaeva::CompositeShape &composite);

}

#endif
