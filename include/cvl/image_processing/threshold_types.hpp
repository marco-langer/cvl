#ifndef CVL_IMAGE_PROCESSING_THRESHOLD_TYPES_HPP
#define CVL_IMAGE_PROCESSING_THRESHOLD_TYPES_HPP

#include <cvl/core/traits.hpp>

namespace cvl {

struct threshold_binary_t {};
struct threshold_binary_inverse_t {};
struct threshold_truncate_t {};
struct threshold_to_zero_t {};
struct threshold_to_zero_inverse_t {};

template <typename T>
concept threshold = detail::is_any_of
<
    T,
    threshold_binary_t, threshold_binary_inverse_t, threshold_truncate_t,
    threshold_to_zero_t, threshold_to_zero_inverse_t
>;

} // namespace cvl

#endif
