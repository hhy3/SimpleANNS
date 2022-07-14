#pragma once

#include "Index.hpp"

/**
 * @brief Base class for index algorithms that incremental insertion and 
 *        removal of vectors.
 * 
 */
class OnlineIndex : public Index {
 public:
  virtual bool build(const std::vector<P>& points) = 0;
  virtual std::vector<int> search(const P& point, int K) = 0;
  virtual bool insert(const P& point) = 0;
  virtual bool erase(const P& point) = 0;
};