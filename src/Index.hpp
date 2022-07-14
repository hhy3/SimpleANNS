#pragma once

#include <vector>

#include "defs.hpp"

template <typename F, int NDIM, typename DistFunc>
class Index {
 public:
  using P = Point<F, NDIM>;
  virtual bool build(const std::vector<P>& points) = 0;
  virtual std::vector<P> query(const P& point, int K) = 0;
};