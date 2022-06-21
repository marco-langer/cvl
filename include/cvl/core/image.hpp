#ifndef CVL_CORE_IMAGE_HPP
#define CVL_CORE_IMAGE_HPP

#include <cvl/core/image_view.hpp>
#include <cvl/core/pixel.hpp>
#include <cvl/core/size.hpp>

#include <concepts>
#include <type_traits>
#include <vector>

namespace cvl {

template <typename Pixel, typename Allocator = std::allocator<Pixel>>
class basic_image
{
public:
    using value_type = Pixel;
    using iterator = typename std::vector<Pixel>::iterator;
    using const_iterator = typename std::vector<Pixel>::const_iterator;
    using view_type = basic_image_view<basic_image<Pixel>, true>;
    using size_type = basic_size<typename point::value_type>;
    using size_value_type = typename point::value_type;

    constexpr static std::size_t channel_count = Pixel::channel_count;

    basic_image() = default;
    basic_image(size_type size)
        : data_(static_cast<std::size_t>(size.width * size.height))
        , view_(point{}, size, data_.begin(), data_.end())
    {}

    basic_image(size_value_type width, size_value_type height)
        : data_(static_cast<std::size_t>(width * height))
        , view_(point{}, size_type(width, height), data_.begin(), data_.end())
    {}

    friend constexpr auto operator==(basic_image const& lhs, basic_image const& rhs)
        -> bool
    {
        return lhs.view_ == rhs.view_;
    }

    friend constexpr auto operator!=(basic_image const& lhs, basic_image const& rhs)
        -> bool
    {
        return lhs.view_ != rhs.view_;
    }

    const auto height() const noexcept -> size_value_type
    {
        return view_.height();
    }
    const auto width() const noexcept -> size_value_type
    {
        return view_.width();
    }
    const auto size() const noexcept -> size_type
    {
        return view_.size();
    }
    constexpr auto view() noexcept -> view_type&
    {
        return view_;
    }
    constexpr auto view() const noexcept -> const view_type&
    {
        return view_;
    }

    constexpr auto begin() noexcept -> iterator
    {
        return std::begin(data_);
    }
    constexpr auto begin() const noexcept -> const_iterator
    {
        return std::begin(data_);
    }
    constexpr auto cbegin() const noexcept -> const_iterator
    {
        return std::cbegin(data_);
    }

    constexpr auto end() noexcept -> iterator
    {
        return std::end(data_);
    }
    constexpr auto end() const noexcept -> const_iterator
    {
        return std::end(data_);
    }
    constexpr auto cend() const noexcept -> const_iterator
    {
        return std::end(data_);
    }

private:
    std::vector<Pixel, Allocator> data_;
    view_type view_;
};

using rgb8_image = cvl::basic_image<rgb8_pixel>;
using gray8_image = cvl::basic_image<gray8_pixel>;
using gray16_image = cvl::basic_image<gray16_pixel>;

namespace detail {

template <typename T>
struct is_image : std::false_type {};

template <typename Pixel, typename Allocator>
struct is_image<basic_image<Pixel, Allocator>> : std::true_type {};

} // namespace detail

template <typename T>
concept image = detail::is_image<T>::value;

} // namespace cvl

#endif
