#pragma once

#include <array>
#include <queue>
#include <vector>

#include "Dist.hpp"
#include "Index.hpp"
#include "defs.hpp"

/**
 * @brief Brute force implementation.
 *
 */
class FlatIndex : public Index {
 public:
  FlatIndex(DistFunc dist) : dist_(dist) {}

  /**
   * @brief Just load vector points.
   *
   */
  bool build(const std::vector<P>& point) override {
    assert(point.size() > 0);
    n_ = point.size();
    dim_ = point[0].size();
    for (size_t i = 1; i < n_; ++i) {
      assert(point[i].size() == dim_);
    }
    points_ = point;
    return true;
  }

  /**
   * @brief Brute force KNN search.
   *        Time Complexity: O(ND + Nlog(K))
   *
   */
  std::vector<P> query(const P& point, int K) override {
    assert(point.size() == dim_ && K <= points_.size());
    std::priority_queue<std::pair<F, int>> pq;
    DistFunc dist;
    for (size_t i = 0; i < points_.size(); ++i) {
      F d = dist_(points_[i], point);
      if (pq.size() < K) {
        pq.push({d, i});
      } else if (d < pq.top().first) {
        pq.pop();
        pq.push({d, i});
      }
    }
    std::vector<P> ret;
    while (pq.size()) {
      auto [_, i] = pq.top();
      pq.pop();
      ret.push_back(points_[i]);
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }

 private:
  DistFunc dist_;
  int n_, dim_;
  std::vector<P> points_;
};