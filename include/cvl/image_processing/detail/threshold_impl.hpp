#ifndef CVL_IMAGE_PROCESSING_DETAIL_THRESHOLD_IMPL
#define CVL_IMAGE_PROCESSING_DETAIL_THRESHOLD_IMPL

#include <cvl/core/image.hpp>
#include <cvl/core/image_view.hpp>
#include <cvl/core/pixel.hpp>
#include <cvl/image_processing/detail/threshold_naive.hpp>
#include <cvl/image_processing/threshold_types.hpp>

#include <immintrin.h>

#include <cassert>
#include <iterator>
#include <limits>

namespace cvl::detail {

template <typename InIt, typename OutIt, typename Scalar, typename Threshold>
void apply_threshold_impl(
    InIt first, InIt last, OutIt d_first,
    Scalar threshold_value, [[maybe_unused]] Threshold threshold)
{
    using pixel_t = typename std::iterator_traits<InIt>::value_type;
    using T = typename pixel_t::value_type;
    static_assert(std::is_same_v<Scalar, T>);
 //   auto constexpr min_value = std::numeric_limits<T>::min();
 //   auto constexpr max_value = std::numeric_limits<T>::max();

    if constexpr (!std::is_same_v<Threshold, threshold_binary_t>)
    {
        apply_threshold_naive(first, last, d_first, threshold_value, threshold);
    }
    else
    {
        auto const n = std::distance(first, last);
        constexpr std::ptrdiff_t simd_elements = 32;
        auto const pixel_sf = _mm256_set1_epi8(static_cast<char>(0x80));
        auto const pixel_threshold = _mm256_set1_epi8(static_cast<std::int8_t>(threshold_value)); // TODO overflow?!
        auto const pixel_threshold2 = _mm256_sub_epi8(pixel_threshold, pixel_sf);

        __m256i pixel_vals_u8x32;
        __m256i result_vals_u8x32;
        std::ptrdiff_t i = 0;
        for (; n - i >= simd_elements; i += simd_elements)
        {
            pixel_vals_u8x32 = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(&*(first + i)));
            pixel_vals_u8x32 = _mm256_sub_epi8(pixel_vals_u8x32, pixel_sf);
            result_vals_u8x32 = _mm256_cmpgt_epi8(pixel_vals_u8x32, pixel_threshold2);
            _mm256_storeu_si256(reinterpret_cast<__m256i*>(&*(d_first + i)), result_vals_u8x32);
        }

        apply_threshold_naive(first + i, last, d_first, threshold_value, threshold);
    }
}

} // namespace cvl::detail

#endif
