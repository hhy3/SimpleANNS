#pragma once

#include "Index.hpp"

namespace sanns {

/**
 * @brief Base class for index algorithms that incremental insertion and
 *        removal of vectors.
 *
 */
class OnlineIndex : public Index {
 public:
  virtual bool build(const std::vector<P>& points,
                     const Config& config = {}) = 0;
  virtual std::vector<int> search(const P& point, int K,
                                  const Config& config = {}) = 0;
  virtual bool insert(const P& point, const Config& config = {}) = 0;
  virtual bool erase(const P& point, const Config& config = {}) = 0;
};

}  // namespace sanns