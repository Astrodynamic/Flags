namespace utils {
template <typename Enum> auto Flags<Enum>::operator==(const Flags& other) -> bool {
  return base::operator==(other);
}

template <typename Enum> auto Flags<Enum>::operator!=(const Flags& other) -> bool {
  return !(*this == other);
}

template <typename Enum> auto Flags<Enum>::operator[](Enum value) const -> bool {
  return base::operator[](static_cast<std::size_t>(value));
}

template <typename Enum> auto Flags<Enum>::operator[](Enum value) -> typename Flags<Enum>::reference {
  return base::operator[](static_cast<std::size_t>(value));
}

template <typename Enum> auto Flags<Enum>::set() -> Flags& {
  return static_cast<Flags&>(base::set());
}

template <typename Enum> auto Flags<Enum>::set(Enum position, bool value) -> Flags& {
  return static_cast<Flags&>(base::set(static_cast<std::size_t>(position), value));
}

template <typename Enum> auto Flags<Enum>::reset() -> Flags& {
  return static_cast<Flags&>(base::reset());
}

template <typename Enum> auto Flags<Enum>::reset(Enum position) -> Flags& {
  return static_cast<Flags&>(base::reset(static_cast<std::size_t>(position)));
}

template <typename Enum> auto Flags<Enum>::flip() -> Flags& {
  return static_cast<Flags&>(base::flip());
}

template <typename Enum> auto Flags<Enum>::flip(Enum position) -> Flags& {
  return static_cast<Flags&>(base::flip(static_cast<std::size_t>(position)));
}

} // namespace utils
