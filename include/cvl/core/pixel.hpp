#ifndef CVL_CORE_PIXEL_HPP
#define CVL_CORE_PIXEL_HPP

#include <cstdint>
#include <type_traits>
#include <utility>

namespace cvl {

template <typename T, std::size_t N>
class basic_pixel
{
public:
    using value_type = T;

    constexpr static std::size_t channel_count = N;

    constexpr basic_pixel() = default;
    constexpr basic_pixel(T channel_value) noexcept : channels{channel_value} {}

    template <typename ...U>
    constexpr basic_pixel(U... channel_values) noexcept
        requires (sizeof...(U) == channel_count && sizeof...(U) != 1)
      : channels{channel_values...}
    {}

    template <std::size_t I>
    constexpr auto get_c() noexcept -> T&
    {
        return channels[I];
    }

    template <std::size_t I>
    constexpr auto get_c() const noexcept -> T const&
    {
        return channels[I];
    }

    constexpr auto operator+=(basic_pixel const& other) noexcept -> basic_pixel<T, N>&
    {
        auto channel_add = [](T& lhs_channel, T rhs_channel)
        {
            lhs_channel += rhs_channel;
        };
        [&]<std::size_t ...Is>(std::index_sequence<Is...>)
        {
            (..., channel_add(channels[Is], other.template get_c<Is>()));
        }(std::make_index_sequence<channel_count>());
        return *this;
    }

    [[nodiscard]] friend inline constexpr auto operator+(
            basic_pixel const& lhs, basic_pixel const& rhs) noexcept
        -> basic_pixel<T, N>
    {
        auto assign_channel = [](auto lhs_channel, auto rhs_channel, auto& result_channel)
        {
            result_channel = lhs_channel + rhs_channel;
        };
        return [&]<std::size_t ...Is>(std::index_sequence<Is...>)
        {
            basic_pixel result;
            (..., assign_channel(lhs.channels[Is], rhs.channels[Is], result.channels[Is]));
            return result;
        }(std::make_index_sequence<basic_pixel::channel_count>());
    }

    [[nodiscard]] friend inline constexpr auto operator==(
            basic_pixel const& lhs, basic_pixel const& rhs) noexcept
        -> bool requires (basic_pixel<T, N>::channel_count == 1)
    {
        return lhs.channels[0] == rhs.channels[0];
    }

private:
    T channels[channel_count]{};
};

using rgb8_pixel = cvl::basic_pixel<std::uint8_t, 3>;
using gray8_pixel = cvl::basic_pixel<std::uint8_t, 1>;
using gray16_pixel = cvl::basic_pixel<std::uint16_t, 1>;

namespace detail {

template <typename T>
struct is_pixel : std::false_type {};

template <typename T, std::size_t N>
struct is_pixel<basic_pixel<T, N>> : std::true_type {};

} // namespace detail

template <typename T>
concept pixel = detail::is_pixel<T>::value;

template <pixel Pixel>
[[nodiscard]] constexpr auto operator>(Pixel const& lhs, Pixel const& rhs) noexcept
    -> bool requires (Pixel::channel_count == 1)
{
    return lhs.template get_c<0>() > rhs.template get_c<0>();
}

template <pixel Pixel>
[[nodiscard]] constexpr auto operator<(Pixel const& lhs, Pixel const& rhs) noexcept
    -> bool requires (Pixel::channel_count == 1)
{
    return lhs.template get_c<0>() < rhs.template get_c<0>();
}

template <pixel Pixel>
[[nodiscard]] constexpr auto operator>=(Pixel const& lhs, Pixel const& rhs) noexcept
    -> bool requires (Pixel::channel_count == 1)
{
    return lhs.template get_c<0>() >= rhs.template get_c<0>();
}

template <pixel Pixel>
[[nodiscard]] constexpr auto operator<=(Pixel const& lhs, Pixel const& rhs) noexcept
    -> bool requires (Pixel::channel_count == 1)
{
    return lhs.template get_c<0>() <= rhs.template get_c<0>();
}

template <pixel Pixel>
[[nodiscard]] constexpr auto operator!=(Pixel const& lhs, Pixel const& rhs) noexcept
    -> bool requires (Pixel::channel_count == 1)
{
    return lhs.template get_c<0>() != rhs.template get_c<0>();
}

} // namespace cvl

#endif
