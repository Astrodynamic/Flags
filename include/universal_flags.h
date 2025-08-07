#pragma once

#include <bitset>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <iterator>
#include <string>

#include "flags_traits.h"

namespace utils {

// A more universal flags container based on Enum and traits mapping
// - Composition over std::bitset
// - No leakage of bitset::reference type
// - Bitwise operators, iteration over set bits, factories
// - Traits allow customizing size and index mapping

template <class Enum, class Traits = enum_flags_traits<Enum>>
class EnumFlags {
  static_assert(std::is_enum_v<Enum>, "Enum must be an enumeration type");

 public:
  using enum_type = Enum;
  static constexpr std::size_t num_bits = Traits::size;

 private:
  std::bitset<num_bits> bits_{};

  static constexpr std::size_t to_index(Enum e) noexcept { return Traits::to_index(e); }

 public:
  // constructors
  constexpr EnumFlags() noexcept = default;
  constexpr EnumFlags(const EnumFlags&) noexcept = default;
  constexpr EnumFlags(EnumFlags&&) noexcept = default;
  ~EnumFlags() = default;

  constexpr EnumFlags& operator=(const EnumFlags&) noexcept = default;
  constexpr EnumFlags& operator=(EnumFlags&&) noexcept = default;

  // Construct from single enumerator
  explicit constexpr EnumFlags(Enum e) noexcept { set(e); }

  // Construct from list of enumerators
  constexpr EnumFlags(std::initializer_list<Enum> es) noexcept {
    for (Enum e : es) set(e);
  }

  // factories
  template <class... Es,
            class = std::enable_if_t<(std::conjunction_v<std::is_same<Enum, std::decay_t<Es>>...>)>>
  static constexpr EnumFlags of(Es... es) noexcept {
    EnumFlags f;
    (f.set(es), ...);
    return f;
  }

  // size and counts
  static constexpr std::size_t size() noexcept { return num_bits; }
  std::size_t count() const noexcept { return bits_.count(); }
  bool any() const noexcept { return bits_.any(); }
  bool none() const noexcept { return bits_.none(); }
  bool all() const noexcept { return bits_.all(); }

  // element access (read-only)
  bool operator[](Enum e) const noexcept { return bits_.test(to_index(e)); }
  bool test(Enum e) const noexcept { return bits_.test(to_index(e)); }

  // modifiers
  EnumFlags& set() noexcept {
    bits_.set();
    return *this;
  }
  EnumFlags& set(Enum e, bool value = true) noexcept {
    bits_.set(to_index(e), value);
    return *this;
  }

  EnumFlags& reset() noexcept {
    bits_.reset();
    return *this;
  }
  EnumFlags& reset(Enum e) noexcept {
    bits_.reset(to_index(e));
    return *this;
  }

  EnumFlags& flip() noexcept {
    bits_.flip();
    return *this;
  }
  EnumFlags& flip(Enum e) noexcept {
    bits_.flip(to_index(e));
    return *this;
  }

  // bulk operations with another flags set
  EnumFlags& set(EnumFlags other) noexcept {
    bits_ |= other.bits_;
    return *this;
  }
  EnumFlags& reset(EnumFlags other) noexcept {
    bits_ &= ~other.bits_;
    return *this;
  }
  EnumFlags& intersect_with(EnumFlags other) noexcept {
    bits_ &= other.bits_;
    return *this;
  }

  // comparisons
  friend bool operator==(const EnumFlags& a, const EnumFlags& b) noexcept { return a.bits_ == b.bits_; }
  friend bool operator!=(const EnumFlags& a, const EnumFlags& b) noexcept { return !(a == b); }

  // bitwise operators
  friend EnumFlags operator~(EnumFlags a) noexcept {
    a.bits_.flip();
    return a;
  }
  friend EnumFlags operator|(EnumFlags a, const EnumFlags& b) noexcept {
    a.bits_ |= b.bits_;
    return a;
  }
  friend EnumFlags operator&(EnumFlags a, const EnumFlags& b) noexcept {
    a.bits_ &= b.bits_;
    return a;
  }
  friend EnumFlags operator^(EnumFlags a, const EnumFlags& b) noexcept {
    a.bits_ ^= b.bits_;
    return a;
  }

  EnumFlags& operator|=(const EnumFlags& other) noexcept {
    bits_ |= other.bits_;
    return *this;
  }
  EnumFlags& operator&=(const EnumFlags& other) noexcept {
    bits_ &= other.bits_;
    return *this;
  }
  EnumFlags& operator^=(const EnumFlags& other) noexcept {
    bits_ ^= other.bits_;
    return *this;
  }

  // operators mixing Enum
  friend EnumFlags operator|(EnumFlags a, Enum e) noexcept { return a.set(e); }
  friend EnumFlags operator|(Enum e, EnumFlags a) noexcept { return a.set(e); }
  friend EnumFlags operator&(EnumFlags a, Enum e) noexcept {
    EnumFlags b(e);
    a.bits_ &= b.bits_;
    return a;
  }
  friend EnumFlags operator^(EnumFlags a, Enum e) noexcept {
    a.flip(e);
    return a;
  }
  EnumFlags& operator|=(Enum e) noexcept { return set(e); }
  EnumFlags& operator&=(Enum e) noexcept {
    EnumFlags b(e);
    bits_ &= b.bits_;
    return *this;
  }
  EnumFlags& operator^=(Enum e) noexcept { return flip(e); }

  // combine two enumerators into flags directly
  friend EnumFlags operator|(Enum a, Enum b) noexcept {
    EnumFlags r;
    r.set(a).set(b);
    return r;
  }

  // mask conversions (only if fits into Unsigned)
  template <class Unsigned = unsigned long long>
  Unsigned to_mask() const noexcept {
    static_assert(std::is_unsigned_v<Unsigned>, "Unsigned must be an unsigned integral type");
    static_assert(num_bits <= std::numeric_limits<Unsigned>::digits,
                  "EnumFlags::to_mask(): not enough bits in Unsigned to hold the flags");
    Unsigned value = 0;
    for (std::size_t i = 0; i < num_bits; ++i) {
      if (bits_.test(i)) value |= (Unsigned{1} << i);
    }
    return value;
  }

  template <class Unsigned = unsigned long long>
  static EnumFlags from_mask(Unsigned value) noexcept {
    static_assert(std::is_unsigned_v<Unsigned>, "Unsigned must be an unsigned integral type");
    static_assert(num_bits <= std::numeric_limits<Unsigned>::digits,
                  "EnumFlags::from_mask(): not enough bits in Unsigned to hold the mask");
    EnumFlags f;
    for (std::size_t i = 0; i < num_bits; ++i) {
      if ((value >> i) & Unsigned{1}) f.bits_.set(i);
    }
    return f;
  }

  // iteration over set bits
  class const_iterator {
   public:
    using value_type = Enum;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_iterator() = default;
    const_iterator(const std::bitset<num_bits>* b, std::size_t idx) : bits_(b), index_(idx) { advance_to_next_set(); }

    value_type operator*() const noexcept { return Traits::from_index(index_); }

    const_iterator& operator++() noexcept {
      ++index_;
      advance_to_next_set();
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    friend bool operator==(const const_iterator& a, const const_iterator& b) noexcept {
      return a.bits_ == b.bits_ && a.index_ == b.index_;
    }
    friend bool operator!=(const const_iterator& a, const const_iterator& b) noexcept { return !(a == b); }

   private:
    void advance_to_next_set() noexcept {
      if (!bits_) return;
      while (index_ < num_bits && !bits_->test(index_)) ++index_;
    }

    const std::bitset<num_bits>* bits_ = nullptr;
    std::size_t index_ = num_bits;
  };

  const_iterator begin() const noexcept { return const_iterator{&bits_, 0}; }
  const_iterator end() const noexcept { return const_iterator{&bits_, num_bits}; }

  // expose string conversion for debugging
  std::string to_string() const { return bits_.to_string(); }
};

} // namespace utils