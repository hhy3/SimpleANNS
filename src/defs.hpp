#pragma once

#include <functional>
#include <vector>

namespace sanns {

using F = float;
using P = std::vector<F>;
using DistFunc = std::function<F(P, P)>;

}  // namespace sanns