#pragma once

#include "defs.hpp"
#include <vector>
#include <fstream>

class SIFTReader {
public:
  static std::vector<P> readf(const char* filename) {
    std::vector<P> points;
    std::ifstream fs(filename, std::ios_base::binary);
    for (int dim; fs.read(reinterpret_cast<char*>(&dim), sizeof(dim)); ) {
      points.push_back(P(dim));
      for (int i = 0; i < dim; ++i) {
        fs.read(reinterpret_cast<char*>(&points.back()[i]), sizeof(float));
      }
    }
    return points;
  }
  static std::vector<std::vector<int>> readi(const char* filename) {
    std::vector<std::vector<int>> points;
    std::ifstream fs(filename, std::ios_base::binary);
    for (int dim; fs.read(reinterpret_cast<char*>(&dim), sizeof(dim)); ) {
      points.push_back(std::vector<int>(dim));
      for (int i = 0; i < dim; ++i) {
        fs.read(reinterpret_cast<char*>(&points.back()[i]), sizeof(int));
      }
    }
    return points;
  }
};