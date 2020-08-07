#ifndef VT_STASH_HPP
// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Stash.hpp:                                           ┃
// ┃ Copyright (c) 2020 viraltaco_                        ┃ 
// ┃ SPDX-License-Identifier: MIT                         ┃
// ┃ <http://www.opensource.org/licenses/MIT>             ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
#define VT_STASH_HPP "2.0.0"

#include <string_view>
#include <utility>

#include <cstdint>

namespace viraltaco_ {
using u8 = std::uint8_t;  
using u64 = std::uint64_t;
using StringView = std::string_view;
template <class CharT> using BasicStringView = std::basic_string_view<CharT>;

template <class CharT = unsigned char> class Stash : BasicStringView<CharT> {
public:
  using Self = Stash;
  using Type = StringView;
  using SizeType = u64;

private: // members  
  static constexpr auto kMaxShift {
    [max = sizeof (SizeType)] (auto i) {
      return (max - i) % max;
    }
  };
  StringView self_;
  SizeType hash_;
  
public: // inits
  constexpr Stash(Type s) noexcept 
    : self_{ std::move(s) }
    , hash_{}
  {
    for (int i = 0; const auto c: self_) {
      if (c > 0x20) {
        hash_ ^= static_cast<u64> (c - 0x20) << kMaxShift(i);
        i += 1;
      }  
    }
  }
  
public: // getters and operator overloads
  constexpr operator SizeType () const noexcept { return hash_; }
  constexpr operator StringView () const noexcept { return self_; }
  
};

inline namespace literals {
  constexpr auto
  operator ""_sh (char const* s, const std::size_t len) noexcept { 
    return static_cast<Stash<>::SizeType> (Stash(StringView{s, len})); 
  }
} // namespace literals
} namespace vt = viraltaco_;

#endif
