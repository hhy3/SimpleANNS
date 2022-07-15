#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>

#include "Space.hpp"

namespace sanns {

class KMeans {
 public:
  KMeans(std::string_view space_name) {
    if (space_name == "l2") {
      dist_func_ = L2Space::getDistFunc();
    } else if (space_name == "ip") {
      dist_func_ = InnerProductSpace::getDistFunc();
    }
  }

  void fit(const std::vector<P>& points, int n_clusters, int max_iter = 300) {
    n_clusters_ = n_clusters;
    n_points_ = points.size();
    ndim_ = points[0].size();
    points_ = points;
    initCentroids(n_clusters);
    for (int i = 0; i < max_iter; ++i) {
      auto dist = calcDistanceToCentroids();
      labels_ = findClustersFromDist(dist);
      centroids_ = findCentroidsFromLabels(labels_);
    }
  }

  int nCluster() { return n_clusters_; }
  int findCluster(int idx) { return labels_[idx]; }
  std::vector<P> centroids() { return centroids_; }
  P centroid(int idx) { return centroids_[idx]; }

  std::vector<std::vector<int>> findLabelsOfEachClusters() {
    std::vector<std::vector<int>> ret(n_clusters_);
    for (int i = 0; i < n_points_; ++i) {
      ret[labels_[i]].push_back(i);
    }
    return ret;
  }

 private:
  DistFunc dist_func_;
  int n_clusters_, n_points_, ndim_;
  std::vector<P> centroids_;
  std::vector<int> labels_;
  std::vector<P> points_;

  void initCentroids(int n_clusters) {
    centroids_.resize(n_clusters);
    for (size_t i = 0; i < n_clusters; ++i) {
      centroids_[i] = points_[i];
    }
  }

  std::vector<std::vector<float>> calcDistanceToCentroids() {
    std::vector<std::vector<float>> dist(n_points_,
                                         std::vector<float>(n_clusters_));
    for (int i = 0; i < n_points_; ++i) {
      for (int j = 0; j < n_clusters_; ++j) {
        dist[i][j] = dist_func_(points_[i], centroids_[j]);
      }
    }
    return dist;
  }

  std::vector<int> findClustersFromDist(
      const std::vector<std::vector<float>>& dist) {
    assert(dist.size() == n_points_ && dist[0].size() == n_clusters_);
    std::vector<int> labels(n_points_);
    for (int i = 0; i < n_points_; ++i) {
      for (int j = 1; j < n_clusters_; ++j) {
        if (dist[i][j] < dist[i][labels[i]]) {
          labels[i] = j;
        }
      }
    }
    return labels;
  }

  std::vector<P> findCentroidsFromLabels(const std::vector<int> labels) {
    std::vector<P> new_centroids(n_clusters_, P(ndim_));
    std::vector<int> cnt(n_clusters_);
    for (int i = 0; i < n_points_; ++i) {
      int label = labels_[i];
      cnt[label]++;
      for (int j = 0; j < ndim_; ++j) {
        new_centroids[label][j] += points_[i][j];
      }
    }
    for (int i = 0; i < n_clusters_; ++i) {
      if (!cnt[i]) {
        continue;
      }
      for (int j = 0; j < ndim_; ++j) {
        new_centroids[i][j] /= cnt[i];
      }
    }
    return new_centroids;
  }
};

}  // namespace sanns