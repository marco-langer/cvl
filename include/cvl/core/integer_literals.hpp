#ifndef CVL_CORE_INTEGER_LITERALS_HPP
#define CVL_CORE_INTEGER_LITERALS_HPP

#include <cstdint>
#include <limits>
#include <version>

namespace cvl::literals::integer_literals {

#ifdef __cpp_size_t_suffix
[[deprecated("use core language size_t literals instead")]]
#endif
consteval std::size_t
operator ""_uz(unsigned long long value)
{
    return static_cast<std::size_t>(value);
}

#ifdef __cpp_size_t_suffix
[[deprecated("use core language ptrdiff_t literals instead")]]
#endif
consteval std::ptrdiff_t
operator ""_z(unsigned long long value)
{
    return static_cast<std::ptrdiff_t>(value);
}

consteval std::uint8_t
operator ""_u8(unsigned long long value)
{
    if (value > std::numeric_limits<std::uint8_t>::max())
    {
        throw;
    }
    return static_cast<std::uint8_t>(value);
}

consteval std::uint16_t
operator ""_u16(unsigned long long value)
{
    if (value > std::numeric_limits<std::uint16_t>::max())
    {
        throw;
    }
    return static_cast<std::uint8_t>(value);
}

} // namespace cvl::literals::integer_literals

#endif
