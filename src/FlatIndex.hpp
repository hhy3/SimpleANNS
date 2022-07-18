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
  /**
   * @brief Construct a new Flat Index object
   *
   * @param space_name: Only l2 and ip are supported.
   * @param dim: Vector space dimensionality.
   */
  FlatIndex(std::string_view space_name, int ndim) : ndim_(ndim) {
    if (space_name == "l2") {
      dist_func_ = L2Space::getDistFunc();
    } else if (space_name == "ip") {
      dist_func_ = InnerProductSpace::getDistFunc();
    }
  }

  /**
   * @brief Just load vector points.
   *        Time Complexity: O(1)
   *
   */
  bool build(std::vector<P>* points, const Config& config = {}) override {
    assert((int)points->size() > 0);
    npoints_ = (int)points->size();
    for (int i = 0; i < npoints_; ++i) {
      assert((int)points->at(i).size() == ndim_);
    }
    points_ = points;
    return true;
  }

  /**
   * @brief Brute force KNN search.
   *        Time Complexity: O(N * D + K * log(K))
   *
   */
  std::vector<int> search(const P& point, int K,
                          const Config& config = {}) override {
    assert((int)point.size() == ndim_ && K <= npoints_);
    std::vector<std::pair<float, int>> dist;
    dist.reserve(npoints_);
    for (int i = 0; i < npoints_; ++i) {
      F d = dist_func_(points_->at(i), point);
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
    assert((int)point.size() == ndim_);
    npoints_++;
    points_->push_back(point);
    return true;
  }

  /**
   * @brief Remove vector.
   *        Time Complexity: O(N * D)
   *
   */
  bool erase(const P& point, const Config& config = {}) {
    auto it = std::find(points_->begin(), points_->end(), point);
    if (it == points_->end()) {
      return false;
    } else {
      points_->erase(it);
      return true;
    }
  }

 private:
  DistFunc dist_func_;
  int npoints_, ndim_;
  std::vector<P>* points_;
};

}  // namespace sanns