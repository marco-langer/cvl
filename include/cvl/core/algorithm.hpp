#ifndef CVL_ALGORITHM_HPP
#define CVL_ALGORITHM_HPP

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>

#include <cassert>

namespace cvl {

template <image_view View1, image_view View2, typename Func>
constexpr void transform_pixels(View1 const& view1, View2& view2, Func func)
{
    assert(view1.size() == view2.size());

    if constexpr (View1::is_1d_traversable && View2::is_1d_traversable)
    {
        std::transform(
            std::begin(view1), std::end(view1),
            std::begin(view2), std::move(func)
        );
    }
    else
    {
        static_assert(detail::dependent_false<View1>); // TODO
    }
}

template <image Image1, image Image2, typename Func>
constexpr void transform_pixels(Image1 const& img1, Image2& img2, Func func)
{
    transform_pixels(img1.view(), img2.view(), std::move(func));
}

} // namespace cvl

#endif
