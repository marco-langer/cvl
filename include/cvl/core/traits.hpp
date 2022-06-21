#ifndef CVL_CORE_TRAITS_HPP
#define CVL_CORE_TRAITS_HPP

#include <type_traits>

namespace cvl {

namespace detail {

template <typename... T>
inline constexpr bool dependent_false = false;

template <typename T, typename ...Ts>
inline constexpr bool is_any_of = (... || std::is_same_v<T, Ts>);

template <typename T>
struct is_integer : std::bool_constant
<
    is_any_of
    <
        T,
        unsigned char, signed char, unsigned short, short, unsigned int, int,
        unsigned long, long, unsigned long long, long long
    >
> {};

template <typename T>
inline constexpr bool is_integer_v = is_integer<T>::value;

} // namespace detail

} // namespace cvl

#endif
