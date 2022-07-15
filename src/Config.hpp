#pragma once

#include <string_view>
#include <unordered_map>

namespace sanns {

using Config = std::unordered_map<std::string_view, std::string_view>;

}  // namespace sanns