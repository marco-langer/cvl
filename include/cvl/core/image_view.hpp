#ifndef CVL_CORE_IMAGE_VIEW_HPP
#define CVL_CORE_IMAGE_VIEW_HPP

#include <cvl/core/point.hpp>
#include <cvl/core/size.hpp>
#include <cvl/core/traits.hpp>

#include <cstring>
#include <iterator>
#include <type_traits>

namespace cvl {

template <typename Image, bool is_1d_traversable_>
class basic_image_view;

namespace detail {

template <typename View>
[[nodiscard]] constexpr auto equal(View const& view1, View const& view2) noexcept -> bool;

} // namespace detail

template <typename Image, bool is_1d_traversable_>
class basic_image_view
{
public:
    using iterator = typename Image::iterator;
    using const_iterator = typename Image::const_iterator;
    using value_type = typename Image::value_type;
    using pixel_value_type = typename value_type::value_type;
    using size_type = basic_size<typename point::value_type>;
    using size_value_type = typename point::value_type;

    constexpr static std::size_t channel_count = Image::channel_count;
    constexpr static bool is_1d_traversable = is_1d_traversable_;

    basic_image_view() = default;
    constexpr basic_image_view(point location, size_type _size, iterator first, iterator last) noexcept
      : location_{location}, size_{_size}, first_{first}, last_{last}
    {}

    [[nodiscard]] friend constexpr auto operator==(basic_image_view const& lhs, basic_image_view const& rhs)
        -> bool
    {
        return (lhs.location_ == rhs.location_) && detail::equal(lhs, rhs);
    }
    [[nodiscard]] friend constexpr auto operator!=(basic_image_view const& lhs, basic_image_view const& rhs)
        -> bool
    {
        return (lhs.location_ != rhs.location_) || !detail::equal(lhs, rhs);
    }

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        return size_;
    }
    [[nodiscard]] constexpr auto height() const noexcept ->size_value_type
    {
        return size_.height;
    }
    [[nodiscard]] constexpr auto width() const noexcept -> size_value_type
    {
        return size_.width;
    }

    [[nodiscard]] constexpr auto begin() noexcept -> iterator
    {
        return first_;
    }
    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator
    {
        return first_;
    }

    [[nodiscard]] constexpr auto end() noexcept -> iterator
    {
        return last_;
    }
    [[nodiscard]] constexpr auto end() const noexcept -> const_iterator
    {
        return last_;
    }

private:
    point location_;
    basic_size<std::ptrdiff_t> size_;
    iterator first_;
    iterator last_;
};

namespace detail {

template <typename T>
struct is_image_view : std::false_type {};

template <typename Image, bool is_1d_traversable>
struct is_image_view<basic_image_view<Image, is_1d_traversable>> : std::true_type {};

} // namespace detail

template <typename T>
concept image_view = detail::is_image_view<T>::value;

namespace detail {

template <typename View>
[[nodiscard]] constexpr auto equal(View const& view1, View const& view2) noexcept
    -> bool
{
    if constexpr(View::is_1d_traversable)
    {
        if constexpr (detail::is_integer_v<typename View::pixel_value_type>)
        {
            return 0 == std::memcmp(
                &*std::cbegin(view1),
                &*std::cbegin(view2),
                static_cast<std::size_t>(view1.width() * view1.height())
            );
        }
        else
        {
            return std::equal(std::cbegin(view1), std::cend(view1), std::cbegin(view2));
        }
    }
    else
    {
        static_assert(detail::dependent_false<View>); // TODO
    }
}

} // namespace detail

} // namespace cvl

#endif