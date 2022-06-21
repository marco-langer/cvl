#ifndef CVL_IMAGE_PROCESSING_MINMAX_HPP
#define CVL_IMAGE_PROCESSING_MINMAX_HPP

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>

#include <cassert>
#include <iterator>
#include <utility>

namespace cvl {

namespace detail {

template <typename InIt>
[[nodiscard]] constexpr auto max_value(InIt first, InIt last)
    -> typename std::iterator_traits<InIt>::value_type
{
    assert(std::distance(first, last) > 0);

    auto max_result = *first++;
    for (; first != last; ++first)
    {
        auto value = *first;
        if (value > max_result)
        {
            max_result = value;
        }
    }

    return max_result;
}

template <typename InIt>
[[nodiscard]] constexpr auto min_value(InIt first, InIt last)
    -> typename std::iterator_traits<InIt>::value_type
{
    assert(std::distance(first, last) > 0);

    auto min_result = *first++;
    for (; first != last; ++first)
    {
        auto value = *first;
        if (value < min_result)
        {
            min_result = value;
        }
    }

    return min_result;
}

template <typename InIt>
[[nodiscard]] constexpr auto minmax_value(InIt first, InIt last)
    -> std::pair
        <
            typename std::iterator_traits<InIt>::value_type,
            typename std::iterator_traits<InIt>::value_type
        >
{
    assert(std::distance(first, last) > 0);

    auto value = *first++;
    auto result = std::pair{value, value};
    for (; first != last; ++first)
    {
        value = *first;
        if (value < result.first)
        {
            result.first = value;
        }
        if (value > result.second)
        {
            result.second = value;
        }
    }

    return result;
}

} // namespace detail

template <image_view View>
[[nodiscard]] constexpr auto max_value(View const& view)
    -> typename View::value_type requires (View::channel_count == 1)
{
    if constexpr (View::is_1d_traversable)
    {
        return detail::max_value(std::cbegin(view), std::cend(view));
    }
    else
    {
        static_assert(detail::dependent_false<View>); // TODO
    }
}

template <image Image>
[[nodiscard]] constexpr auto max_value(Image const& img)
    -> typename Image::value_type requires (Image::channel_count == 1)
{
    return max_value(img.view());
}

template <image_view View>
[[nodiscard]] constexpr auto min_value(View const& view)
    -> typename View::value_type requires (View::channel_count == 1)
{
    if constexpr (View::is_1d_traversable)
    {
        return detail::min_value(std::cbegin(view), std::cend(view));
    }
    else
    {
        static_assert(detail::dependent_false<View>); // TODO
    }
}

template <image Image>
[[nodiscard]] constexpr auto min_value(Image const& img)
    -> typename Image::value_type requires (Image::channel_count == 1)
{
    return min_value(img.view());
}

template <image_view View>
[[nodiscard]] constexpr auto minmax_value(View const& view)
    -> std::pair
        <
            typename View::value_type,
            typename View::value_type
        > requires (View::channel_count == 1)
{
    if constexpr (View::is_1d_traversable)
    {
        return detail::minmax_value(std::cbegin(view), std::cend(view));
    }
    else
    {
        static_assert(detail::dependent_false<View>); // TODO
    }
}

template <image Image>
[[nodiscard]] constexpr auto minmax_value(Image const& img)
    -> std::pair
        <
            typename Image::value_type,
            typename Image::value_type
        > requires (Image::channel_count == 1)
{
    return minmax_value(img.view());
}

} // namespace cvl

#endif
