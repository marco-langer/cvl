#include <cvl/cvl.hpp>

void threshold_cvl_binary(
    cvl::gray8_image const& gray8_img,
    cvl::gray8_image& result_gray8_img, std::uint8_t threshold)
{
    cvl::apply_threshold(gray8_img, result_gray8_img, threshold, cvl::threshold_binary_t{});
}

void threshold_cvl_binary_inv(
    cvl::gray8_image const& gray8_img,
    cvl::gray8_image& result_gray8_img, std::uint8_t threshold)
{
    cvl::apply_threshold(gray8_img, result_gray8_img, threshold, cvl::threshold_binary_inverse_t{});
}

void threshold_cvl_trunc(
    cvl::gray8_image const& gray8_img,
    cvl::gray8_image& result_gray8_img, std::uint8_t threshold)
{
    cvl::apply_threshold(gray8_img, result_gray8_img, threshold, cvl::threshold_truncate_t{});
}
