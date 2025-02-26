#pragma once

#include "common.h"

namespace enums {
template <typename Enum> struct Meta {
  static const char *name;
  static const std::vector<std::string> description;
};
} // namespace enums

#define ENUM(type, ...)                                                                                    \
namespace enums {                                                                                          \
  enum class type { __VA_ARGS__, Count };                                                                  \
  template <> const char *Meta<type>::name = #type;                                                        \
  template <> const std::vector<std::string> Meta<type>::description = utils::tokenization(#__VA_ARGS__);  \
} // namespace enums
