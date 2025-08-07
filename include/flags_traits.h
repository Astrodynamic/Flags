#pragma once

#include <cstddef>
#include <type_traits>

namespace utils {

// Default traits: assumes Enum has contiguous 0..COUNT-1 domain and defines COUNT enumerator
// Users can specialize this for non-contiguous enums or custom sizing/mapping
template <class Enum>
struct enum_flags_traits {
  static_assert(std::is_enum_v<Enum>, "Enum must be an enumeration type");

  static constexpr std::size_t size = static_cast<std::size_t>(Enum::COUNT);

  static constexpr std::size_t to_index(Enum value) noexcept {
    return static_cast<std::size_t>(value);
  }

  static constexpr Enum from_index(std::size_t index) noexcept {
    return static_cast<Enum>(index);
  }
};

} // namespace utils