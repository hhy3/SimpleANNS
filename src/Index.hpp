#pragma once

#include <vector>

#include "defs.hpp"

/**
 * @brief Base class for all index algorithms.
 *
 */
class Index {
 public:
  virtual bool build(const std::vector<P>& points) = 0;
  virtual std::vector<P> query(const P& point, int K) = 0;
};