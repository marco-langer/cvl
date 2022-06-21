#ifndef CVL_CORE_SIZE_HPP
#define CVL_CORE_SIZE_HPP

#include <cstdint>

namespace cvl {

template <typename T>
struct basic_size
{
    using value_type = T;

    T width{};
    T height{};

    friend constexpr auto operator==(basic_size const& lhs, basic_size const& rhs)
        -> bool
    {
        return lhs.width == rhs.width && lhs.height == rhs.height;
    }
};

} // namespace cvl

#endif