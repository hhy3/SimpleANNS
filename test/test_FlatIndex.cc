#include <iostream>
#include <unordered_set>

#include "FlatIndex.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  auto base = SIFTReader::readf("../data/siftsmall/siftsmall_base.fvecs");
  auto query = SIFTReader::readf("../data/siftsmall/siftsmall_query.fvecs");
  auto truth =
      SIFTReader::readi("../data/siftsmall/siftsmall_groundtruth.ivecs");
  constexpr int K = 100, dim = 128;
  FlatIndex index("l2", dim);
  index.build(base);
  int64_t cnt = 0;
  for (int i = 0; i < (int)query.size(); ++i) {
    auto ret = index.search(query[i], K);
    std::unordered_set<int> st(ret.begin(), ret.end());
    for (int j = 0; j < K; ++j) {
      if (st.count(truth[i][j])) {
        cnt++;
      }
    }
  }
  cout << "FlatIndex recall: " << cnt * 100.0 / query.size() / K << "%\n";
}