#ifndef CVL_IMAGE_PROCESSING_COLOR_CONVERT_HPP
#define CVL_IMAGE_PROCESSING_COLOR_CONVERT_HPP

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>
#include <cvl/core/traits.hpp>
#include <cvl/image_processing/detail/color_convert_naive.hpp>

#include <cassert>

namespace cvl {

template <bool is_1d_traversable1, bool is_1d_traversable2>
void inline color_convert(
    basic_image_view<rgb8_image, is_1d_traversable1> const& rgb8_view,
    basic_image_view<gray8_image, is_1d_traversable2>& gray8_view)
{
    assert(rgb8_view.size() == gray8_view.size());

    if constexpr (is_1d_traversable1 && is_1d_traversable2)
    {
        detail::color_convert_naive(rgb8_view, gray8_view);
    }
    else
    {
        static_assert(detail::dependent_false<is_1d_traversable1>); // TODO
    }
}

template <typename = void>
void inline color_convert(rgb8_image const& rgb8_img, gray8_image& gray8_img)
{
    return color_convert(rgb8_img.view(), gray8_img.view());
}

} // namespace cvl

#endif
