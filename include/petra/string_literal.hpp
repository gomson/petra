// Copyright Jacqueline Kay 2017
// Distributed under the MIT License.
// See accompanying LICENSE.md or https://opensource.org/licenses/MIT

#pragma once

#include <array>
#include <string>

#include <cstring>

#include "petra/detail/string_literal.hpp"
#include "petra/utilities/fold.hpp"
#include "petra/utilities/sequence.hpp"
#include "petra/utilities/tuple.hpp"

namespace petra {

  template<typename T, T... Pack>
  struct string_literal {
    using value_type = const char*;
    static constexpr const char* value() { return data; };

    static constexpr auto size() { return sizeof...(Pack); };
    static constexpr auto char_at(unsigned i) { return data[i]; };

  private:
    static constexpr char data[sizeof...(Pack) + 1] = {Pack..., '\0'};
  };

  template<typename T, T... P>
  static constexpr bool empty(const string_literal<T, P...>&) {
    return sizeof...(P) == 0;
  }

  template<typename T, T... P, typename S, S... Q>
  static constexpr bool equal(const string_literal<T, P...>&,
                              const string_literal<S, Q...>&) {
    if (sizeof...(P) != sizeof...(Q)) {
      return false;
    } else {
      return detail::compare<T, P...>::template apply<S, Q...>(
          std::make_index_sequence<sizeof...(P)>{});
    }
  }

  template<typename T, T... P>
  static constexpr bool equal(const string_literal<T, P...>&, const char* b) {
    if (utilities::length(b) != sizeof...(P)) {
      return false;
    } else {
      return detail::compare<T, P...>::apply(
          b, std::make_index_sequence<sizeof...(P)>{});
    }
  }

  template<typename T, T... P>
  constexpr bool operator==(const string_literal<T, P...>& a, const char* b) {
    return equal(a, b);
  }

  template<typename T, T... P, typename S, S... Q>
  constexpr bool operator==(const string_literal<T, P...>& a,
                            const string_literal<S, Q...>& b) {
    return equal(a, b);
  }

#define PETRA_STRING_LITERAL(Value)                                            \
  []() {                                                                       \
    struct tmp {                                                               \
      static constexpr decltype(auto) value() { return Value; }                \
      static constexpr auto char_at(unsigned i) { return value()[i]; };        \
    };                                                                         \
    return petra::detail::from_string_literal(                                 \
        tmp{}, std::make_index_sequence<sizeof(Value)>{});                     \
  }()

#ifdef PETRA_USE_UDL
  namespace literals {
    template<typename T, T... Pack>
    constexpr auto operator"" _s() {
      return string_literal<T, Pack...>{};
    }
  }  // namespace literals
#endif

}  // namespace petra
