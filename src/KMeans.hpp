#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>

#include "defs.hpp"

namespace sanns {

class KMeans {
 public:
  KMeans(DistFunc dist_func) : dist_func_(dist_func) {}

  void fit(std::vector<P>* points, int n_clusters, int max_iter = 300) {
    n_clusters_ = n_clusters;
    npoints_ = points->size();
    dim_ = points->at(0).size();
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

  std::vector<std::vector<int>> findComponents() {
    std::vector<std::vector<int>> ret(n_clusters_);
    for (int i = 0; i < npoints_; ++i) {
      ret[labels_[i]].push_back(i);
    }
    return ret;
  }

 private:
  DistFunc dist_func_;
  int n_clusters_, npoints_, dim_;
  std::vector<P> centroids_;
  std::vector<int> labels_;
  std::vector<P>* points_;

  void initCentroids(int n_clusters) {
    centroids_.resize(n_clusters);
    for (size_t i = 0; i < n_clusters; ++i) {
      centroids_[i] = points_->at(i);
    }
  }

  std::vector<std::vector<float>> calcDistanceToCentroids() {
    std::vector<std::vector<float>> dist(npoints_,
                                         std::vector<float>(n_clusters_));
    for (int i = 0; i < npoints_; ++i) {
      for (int j = 0; j < n_clusters_; ++j) {
        dist[i][j] = dist_func_(points_->at(i), centroids_[j]);
      }
    }
    return dist;
  }

  std::vector<int> findClustersFromDist(
      const std::vector<std::vector<float>>& dist) {
    assert(dist.size() == npoints_ && dist[0].size() == n_clusters_);
    std::vector<int> labels(npoints_);
    for (int i = 0; i < npoints_; ++i) {
      for (int j = 1; j < n_clusters_; ++j) {
        if (dist[i][j] < dist[i][labels[i]]) {
          labels[i] = j;
        }
      }
    }
    return labels;
  }

  std::vector<P> findCentroidsFromLabels(const std::vector<int> labels) {
    std::vector<P> new_centroids(n_clusters_, P(dim_));
    std::vector<int> cnt(n_clusters_);
    for (int i = 0; i < npoints_; ++i) {
      int label = labels_[i];
      cnt[label]++;
      for (int j = 0; j < dim_; ++j) {
        new_centroids[label][j] += points_->at(i)[j];
      }
    }
    for (int i = 0; i < n_clusters_; ++i) {
      if (!cnt[i]) {
        continue;
      }
      for (int j = 0; j < dim_; ++j) {
        new_centroids[i][j] /= cnt[i];
      }
    }
    return new_centroids;
  }
};

}  // namespace sanns