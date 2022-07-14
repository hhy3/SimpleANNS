#pragma once

#include <cassert>

/**
 * @brief L2 norm between two vectors.
 * 
 */
class L2Dist {
 public:
  auto operator()(const auto& x, const auto& y) {
    assert(x.size() > 0 && x.size() == y.size());
    auto d = decltype(x[0]){};
    for (size_t i = 0; i < x.size(); ++i) {
      d += (x[i] - y[i]) * (x[i] - y[i]);
    }
    return d;
  }
};

/**
 * @brief Inner product between two vectors.
 *        Need to normalize vectors before calculation.
 * 
 */
class InnerProductDist {
 public:
  auto operator()(const auto& x, const auto& y) {
    assert(x.size() > 0 && x.size() == y.size());
    auto d = decltype(x[0]){};
    for (size_t i = 0; i < x.size(); ++i) {
      d += x[i] * y[i];
    }
    return 1.0 - d;
  }
};

