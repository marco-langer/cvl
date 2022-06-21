#ifndef CVL_IMAGE_PROCESSING_DETAIL_THRESHOLD_NAIVE_HPP
#define CVL_IMAGE_PROCESSING_DETAIL_THRESHOLD_NAIVE_HPP

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>
#include <cvl/core/pixel.hpp>
#include <cvl/image_processing/threshold_types.hpp>

#include <cassert>
#include <iterator>
#include <limits>

namespace cvl::detail {

template <typename InIt, typename OutIt, typename Scalar, typename Threshold>
void apply_threshold_naive(InIt first, InIt last, OutIt d_first, Scalar threshold_value, Threshold)
{
    using pixel_t = typename std::iterator_traits<InIt>::value_type;
    using T = typename pixel_t::value_type;
    static_assert(std::is_same_v<Scalar, T>);
    auto constexpr min_value = std::numeric_limits<T>::min();
    auto constexpr max_value = std::numeric_limits<T>::max();
    auto const threshold_pixel = pixel_t{threshold_value};

    for (; first != last; ++first, ++d_first)
    {
        auto const value = *first;

        if constexpr (std::is_same_v<Threshold, threshold_binary_t>)
        {
            *d_first = value >= threshold_pixel ? max_value : min_value;
        }
        else if constexpr (std::is_same_v<Threshold, threshold_binary_inverse_t>)
        {
            *d_first = value >= threshold_pixel ? min_value : max_value;
        }
        else if constexpr (std::is_same_v<Threshold, threshold_truncate_t>)
        {
            *d_first = value >= threshold_pixel ? threshold_pixel : value;
        }
        else if constexpr (std::is_same_v<Threshold, threshold_to_zero_t>)
        {
            *d_first = value >= threshold_pixel ? value : min_value;
        }
        else if constexpr (std::is_same_v<Threshold, threshold_to_zero_inverse_t>)
        {
            *d_first = value >= threshold_pixel ? min_value : value;
        }
        else
        {
            static_assert(detail::dependent_false<Threshold>);
        }
    }
}

template <bool is_1d_traversable, typename Threshold>
void inline apply_threshold_naive(
    basic_image_view<gray8_image, is_1d_traversable> const& gray8_view,
    basic_image_view<gray8_image, is_1d_traversable>& gray8_result_view,
    typename gray8_pixel::value_type threshold_value,
    Threshold threshold)
{
    assert(gray8_view.size() == gray8_result_view.size());

    if constexpr (is_1d_traversable)
    {
        apply_threshold_naive(
            std::cbegin(gray8_view),
            std::cend(gray8_view),
            std::begin(gray8_result_view),
            threshold_value, threshold
        );
    }
    else
    {
        static_assert(detail::dependent_false<is_1d_traversable>); // TODO
    }
}

template <typename Threshold>
void inline apply_threshold_naive(
    gray8_image const& gray8_img,
    gray8_image& gray8_result_img,
    typename gray8_pixel::value_type threshold_value,
    Threshold threshold)
{
    apply_threshold_naive(
        gray8_img.view(), gray8_result_img.view(), threshold_value, threshold
    );
}

} // namespace detail

#endif
