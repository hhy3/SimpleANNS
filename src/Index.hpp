#pragma once

#include <vector>

#include "Config.hpp"
#include "defs.hpp"

namespace sanns {

/**
 * @brief Base class for all index algorithms.
 *
 */
class Index {
 public:
  virtual bool build(std::vector<P>* points, const Config& config = {}) = 0;
  virtual std::vector<int> search(const P& point, int K,
                                  const Config& config = {}) = 0;
};

}  // namespace sanns