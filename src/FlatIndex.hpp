#pragma once

#include <array>
#include <queue>
#include <vector>

#include "Dist.hpp"
#include "Index.hpp"
#include "defs.hpp"

template <typename F, int NDIM, typename DistFunc>
class FlatIndex : public Index<F, NDIM, DistFunc> {
 public:
  using P = Point<F, NDIM>;
  bool build(const std::vector<P>& point) override {
    points_ = point;
    return true;
  }

  std::vector<P> query(const P& point, int K) override {
    assert(point.size() == NDIM && K <= points_.size());
    std::priority_queue<std::pair<float, int>> pq;
    DistFunc dist;
    for (size_t i = 0; i < points_.size(); ++i) {
      F d = dist(points_[i], point);
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
  std::vector<P> points_;
};