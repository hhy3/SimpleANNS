#pragma once

#include <string_view>

#include "Config.hpp"
#include "Index.hpp"
#include "KMeans.hpp"
#include "Space.hpp"
#include "defs.hpp"

namespace sanns {

/**
 * @brief IVF_FLAT index implementation.
 *
 */
class IVFFlatIndex : public Index {
 public:
  /**
   * @brief Construct a new IVFFlatIndex object
   *
   * @param space_name: Only l2 and ip are supported.
   * @param dim: Vector space dimensionality.
   */
  IVFFlatIndex(std::string_view space_name, int dim) : dim_(dim) {
    if (space_name == "l2") {
      dist_func_ = L2Space::getDistFunc();
    } else if (space_name == "ip") {
      dist_func_ = InnerProductSpace::getDistFunc();
    }
  }

  /**
   * @brief Clustering vectors into nlist clusters using k-menas algorithm.
   *        Time Complexity: O(N * nlist * D * max_iter)
   *
   */
  bool build(std::vector<P>* points, const Config& config) override {
    assert(config.count("nlist"));
    nlist_ = std::stoi(config.at("nlist"));
    int max_iter = 10;
    if (config.count("max_iter")) {
      max_iter = stoi(config.at("max_iter"));
    }
    points_ = points;
    KMeans kmeans(dist_func_);
    kmeans.fit(points_, nlist_, max_iter);
    centroids_ = kmeans.centroids();
    components_ = kmeans.findComponents();
    return true;
  }

  /**
   * @brief Search vectors in nprob nearest clusters.
   *        Time Complexity: Worst case O(N * D + K * log(K))
   *                         Average case O((nlist + N * nprob / nlist) * D)
   *
   */
  std::vector<int> search(const P& point, int K,
                          const Config& config) override {
    assert(config.count("nprob"));
    int nprob = std::stoi(config.at("nprob"));
    assert(nprob <= nlist_);
    std::vector<std::pair<float, int>> distc, distp;
    distc.reserve(nlist_);
    distp.reserve(n_points_);
    for (int i = 0; i < nlist_; ++i) {
      F d = dist_func_(point, centroids_[i]);
      distc.emplace_back(d, i);
    }
    std::nth_element(distc.begin(), distc.begin() + nprob - 1, distc.end());
    std::sort(distc.begin(), distc.begin() + nprob);
    for (int i = 0; i < nprob; ++i) {
      for (auto& idx : components_[distc[i].second]) {
        F d = dist_func_(point, points_->at(idx));
        distp.emplace_back(d, idx);
      }
    }
    std::nth_element(distp.begin(), distp.begin() + K - 1, distp.end());
    std::sort(distp.begin(), distp.begin() + K);
    std::vector<int> ret;
    for (int i = 0; i < K; ++i) {
      ret.push_back(distp[i].second);
    }
    return ret;
  }

 private:
  DistFunc dist_func_;
  int n_points_, dim_, nlist_;
  std::vector<P>* points_;
  std::vector<P> centroids_;
  std::vector<std::vector<int>> components_;
};

}  // namespace sanns