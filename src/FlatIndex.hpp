#pragma once

#include <array>
#include <queue>
#include <string_view>
#include <vector>

#include "OnlineIndex.hpp"
#include "Space.hpp"
#include "defs.hpp"

/**
 * @brief Brute force implementation.
 *
 */
class FlatIndex : public OnlineIndex {
 public:
  FlatIndex(std::string_view space_name, int dim) : dim_(dim) {
    if (space_name == "l2") {
      dist_ = L2Space::getDistFunc();
    } else if (space_name == "ip") {
      dist_ = InnerProductSpace::getDistFunc();
    }
  }

  /**
   * @brief Just load vector points.
   *
   */
  bool build(const std::vector<P>& point) override {
    assert(point.size() > 0);
    n_ = point.size();
    for (size_t i = 0; i < n_; ++i) {
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
  std::vector<P> search(const P& point, int K) override {
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

  /**
   * @brief Add new vector.
   *        Time Complexity: O(D)
   * 
   */
  bool insert(const P& point) {
    assert(point.size() == dim_);
    n_++;
    points_.push_back(point);
    return true;
  }

  bool erase(const P& point) {
    auto it = std::find(points_.begin(), points_.end(), point); 
    if (it == points_.end()) {
      return false;
    } else {
      points_.erase(it);
      return true;
    }
  }

 private:
  DistFunc dist_;
  int n_, dim_;
  std::vector<P> points_;
};