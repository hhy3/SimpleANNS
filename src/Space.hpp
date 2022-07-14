#pragma once

#include <cassert>

#include "defs.hpp"

/**
 * @brief L2 space
 *
 */
class L2Space {
 public:
  static DistFunc getDistFunc() {
    return DistFunc([](const P& x, const P& y) -> F {
      assert(x.size() == y.size());
      F d = 0.0;
      for (size_t i = 0; i < x.size(); ++i) {
        d += (x[i] - y[i]) * (x[i] - y[i]);
      }
      return d;
    });
  }
};

/**
 * @brief Inner product space
 *        Need to normalize vectors before calculation.
 *
 */
class InnerProductSpace {
 public:
  static DistFunc getDistFunc() {
    return DistFunc([](const auto& x, const auto& y) {
      assert(x.size() > 0 && x.size() == y.size());
      F d = 0.0;
      for (size_t i = 0; i < x.size(); ++i) {
        d += x[i] * y[i];
      }
      return 1.0 - d;
    });
  }
};
