#include "common.h"

#include <algorithm>
#include <sstream>

namespace utils {
auto tokenization(const std::string &value, char delimiter) -> std::vector<std::string> {
  std::vector<std::string> result;

  std::string token;
  std::istringstream stream(value);
  while (std::getline(stream, token, delimiter)) {
    token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
    result.push_back(token);
  }

  return result;
}
} // namespace utils
