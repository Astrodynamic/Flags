#pragma once

#include <string>
#include <vector>

namespace utils {
auto tokenization(const std::string &value, char delimiter = ',') -> std::vector<std::string>;
} // namespace utils
