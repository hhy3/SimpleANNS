#include <iomanip>
#include <iostream>
#include <unordered_set>

#include "Config.hpp"
#include "IVFFlatIndex.hpp"
#include "utils.hpp"

using namespace std;

int main() {
  cout << fixed << setprecision(3);
  cout << "IVFFlatIndex:\n";
  auto base = SIFTReader::readf("../data/siftsmall/siftsmall_base.fvecs");
  auto query = SIFTReader::readf("../data/siftsmall/siftsmall_query.fvecs");
  auto truth =
      SIFTReader::readi("../data/siftsmall/siftsmall_groundtruth.ivecs");
  constexpr int K = 100, dim = 128;
  sanns::IVFFlatIndex index("l2", dim);
  sanns::Config build_config, search_config;
  build_config["nlist"] = "128";
  search_config["nprob"] = "20";
  auto start = clock();
  index.build(&base, build_config);
  auto buildTime = clock() - start;
  cout << "    build time: " << 1000.0 * double(buildTime) / CLOCKS_PER_SEC
       << "ms\n";
  start = clock();
  int64_t cnt = 0;
  for (int i = 0; i < (int)query.size(); ++i) {
    auto ret = index.search(query[i], K, search_config);
    std::unordered_set<int> st(ret.begin(), ret.end());
    for (int j = 0; j < K; ++j) {
      if (st.count(truth[i][j])) {
        cnt++;
      }
    }
  }
  auto searchTime = clock() - start;
  cout << "    search time: "
       << 1000.0 * double(searchTime) / CLOCKS_PER_SEC / query.size()
       << "ms/q\n";
  cout << "    recall: " << cnt * 100.0 / query.size() / K << "%\n";
}