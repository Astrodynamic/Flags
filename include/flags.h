#pragma once

#include <bitset>

namespace utils {
template <typename Enum> class Flags final : protected std::bitset<static_cast<std::size_t>(Enum::COUNT)> {
public:
  static_assert(std::is_enum_v<Enum>, "Enum must be an enumeration type");

  using base = std::bitset<static_cast<std::size_t>(Enum::COUNT)>;
  using reference = typename base::reference;

  using base::operator[];

  Flags() = default;
  Flags(const Flags& other) = default;
  Flags(Flags&& other) = default;
  ~Flags() = default;

  auto operator=(const Flags& other) -> Flags& = default;
  auto operator=(Flags&& other) -> Flags& = default;

  [[nodiscard]] auto operator==(const Flags& other) -> bool;
  [[nodiscard]] auto operator!=(const Flags& other) -> bool;

  [[nodiscard]] auto operator[](Enum value) const -> bool;
  [[nodiscard]] auto operator[](Enum value) -> reference;
  
  auto set() -> Flags&;
  auto set(Enum position, bool value = true) -> Flags&;

  auto reset() ->Flags&;
  auto reset(Enum position) -> Flags&;

  auto flip() ->Flags&;
  auto flip(Enum position) -> Flags&;
};
} // namespace utils

#include "flags.tpp"
