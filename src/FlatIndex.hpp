#pragma once

#include <array>
#include <queue>
#include <string_view>
#include <vector>

#include "Config.hpp"
#include "OnlineIndex.hpp"
#include "Space.hpp"
#include "defs.hpp"

namespace sanns {

/**
 * @brief Brute force implementation.
 *
 */
class FlatIndex : public OnlineIndex {
 public:
  FlatIndex(std::string_view space_name, int dim) : dim_(dim) {
    if (space_name == "l2") {
      dist_func_ = L2Space::getDistFunc();
    } else if (space_name == "ip") {
      dist_func_ = InnerProductSpace::getDistFunc();
    }
  }

  /**
   * @brief Just load vector points.
   *
   */
  bool build(const std::vector<P>& point, const Config& config = {}) override {
    assert((int)point.size() > 0);
    n_ = (int)point.size();
    for (int i = 0; i < n_; ++i) {
      assert((int)point[i].size() == dim_);
    }
    points_ = point;
    return true;
  }

  /**
   * @brief Brute force KNN search.
   *        Time Complexity: O(ND + Klog(K))
   *
   */
  std::vector<int> search(const P& point, int K,
                          const Config& config = {}) override {
    assert((int)point.size() == dim_ && K <= (int)points_.size());
    std::vector<std::pair<float, int>> dist;
    dist.reserve(n_);
    for (int i = 0; i < (int)points_.size(); ++i) {
      F d = dist_func_(points_[i], point);
      dist.emplace_back(d, i);
    }
    std::nth_element(dist.begin(), dist.begin() + K - 1, dist.end());
    std::sort(dist.begin(), dist.begin() + K);
    std::vector<int> ret(K);
    for (int i = 0; i < K; ++i) {
      ret[i] = dist[i].second;
    }
    return ret;
  }

  /**
   * @brief Add new vector.
   *        Time Complexity: O(D)
   *
   */
  bool insert(const P& point, const Config& config = {}) {
    assert((int)point.size() == dim_);
    n_++;
    points_.push_back(point);
    return true;
  }

  /**
   * @brief Remove vector.
   *        Time Complexity: O(ND)
   *
   */
  bool erase(const P& point, const Config& config = {}) {
    auto it = std::find(points_.begin(), points_.end(), point);
    if (it == points_.end()) {
      return false;
    } else {
      points_.erase(it);
      return true;
    }
  }

 private:
  DistFunc dist_func_;
  int n_, dim_;
  std::vector<P> points_;
};

}  // namespace sanns