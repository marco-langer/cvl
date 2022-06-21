#ifndef CVL_IMAGE_PROCESSING_DETAIL_COLOR_CONVERT_NAIVE_HPP
#define CVL_IMAGE_PROCESSING_DETAIL_COLOR_CONVERT_NAIVE_HPP

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>
#include <cvl/core/pixel.hpp>
#include <cvl/core/algorithm.hpp>

#include <cstdint>

namespace cvl::detail {

template <bool is_1d_traversable1, bool is_1d_traversable2>
void inline color_convert_naive(
    basic_image_view<rgb8_image, is_1d_traversable1> const& rgb8_view,
    basic_image_view<gray8_image, is_1d_traversable2>& gray8_view)
{
    auto cc_op = [](auto&& p)
    {
        return gray8_pixel{
            static_cast<std::uint8_t>(
                0.299 * p.template get_c<0>()
                + 0.587 * p.template get_c<1>()
                + 0.114 * p.template get_c<2>()
            )
        };
    };

    transform_pixels(rgb8_view, gray8_view, cc_op);
}

template <typename = void>
void inline color_convert_naive(rgb8_image const& rgb8_img, gray8_image& gray8_img)
{
    return color_convert_naive(rgb8_img.view(), gray8_img.view());
}

} // namespace cvl::detail

#endif
