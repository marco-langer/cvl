#ifndef CVL_CORE_POINT_HPP
#define CVL_CORE_POINT_HPP

#include <cstdint>

namespace cvl {

template <typename T>
struct basic_point
{
    using value_type = T;

    T x{};
    T y{};

    friend constexpr auto operator==(basic_point const& lhs, basic_point const& rhs)
        -> bool
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

using point = basic_point<std::ptrdiff_t>;

} // namespace cvl

#endif
