#include "enum.h"

#include <iostream>

namespace utils {
template <typename Enum> auto Flags<Enum>::operator[](Enum value) const -> const typename Flags<Enum>::reference {
  return base::operator[](static_cast<std::size_t>(value));
}

template <typename Enum> auto Flags<Enum>::operator[](Enum value) -> typename Flags<Enum>::reference {
  return base::operator[](static_cast<std::size_t>(value));
}

template <typename Enum> auto Flags<Enum>::set() -> Flags& {
  base::set();
  return *this;
}

template <typename Enum> auto Flags<Enum>::set(Enum position, bool value) -> Flags& {
  base::set(static_cast<std::size_t>(position), value);
  return *this;
}

template <typename Enum> auto Flags<Enum>::reset() -> Flags& {
  base::reset();
  return *this;
}

template <typename Enum> auto Flags<Enum>::reset(Enum position) -> Flags& {
  base::reset(static_cast<std::size_t>(position));
  return *this;
}

template <typename Enum> auto Flags<Enum>::flip() -> Flags& {
  base::flip();
  return *this;
}

template <typename Enum> auto Flags<Enum>::flip(Enum position) -> Flags& {
  base::flip(static_cast<std::size_t>(position));
  return *this;
}

} // namespace utils

template <typename Enum> 
auto operator<<(std::ostream& os, const utils::Flags<Enum>& flags) -> std::ostream& {
  os << "Seted {\n";
  for (std::size_t i{}; i < static_cast<std::size_t>(Enum::Count); ++i) {
    if (flags[i]) {
      os << ' ' << enums::Meta<Enum>::name << "::" << enums::Meta<Enum>::description[i] << '\n';
    }
  }
  return os << "}\n";
}
