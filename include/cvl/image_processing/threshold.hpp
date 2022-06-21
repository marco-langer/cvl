#ifndef CVL_IMAGE_PROCESSING_THRESHOLD_HPP
#define CVL_IMAGE_PROCESSING_THRESHOLD_HPP

#include <cvl/image_processing/detail/threshold_impl.hpp>
#include <cvl/image_processing/threshold_types.hpp>

#include <cassert>

namespace cvl {

template <bool is_1d_traversable, threshold Threshold>
void inline apply_threshold(
    basic_image_view<gray8_image, is_1d_traversable> const& gray8_view,
    basic_image_view<gray8_image, is_1d_traversable>& gray8_result_view,
    typename gray8_pixel::value_type threshold_value, Threshold threshold)
{
    assert(gray8_view.size() == gray8_result_view.size());

    if constexpr (is_1d_traversable)
    {
        detail::apply_threshold_impl(
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

template <threshold Threshold>
void inline apply_threshold(
    gray8_image const& gray8_img,
    gray8_image& gray8_result_img,
    typename gray8_pixel::value_type threshold_value, Threshold threshold)
{
    return apply_threshold(
        gray8_img.view(), gray8_result_img.view(), threshold_value, threshold
    );
}

} // namespace cvl

#endif
