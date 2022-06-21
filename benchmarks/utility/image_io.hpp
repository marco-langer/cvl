#ifndef CVL_BENCHMARK_UTILITY_IMAGE_IO_HPP
#define CVL_BENCHMARK_UTILITY_IMAGE_IO_HPP

#include <cvl/core/image.hpp>

#include <opencv2/core/mat.hpp>

#include <filesystem>

namespace utility {

auto read_image_opencv(std::filesystem::path const& filepath) -> cv::Mat;
auto read_image(std::filesystem::path const& filepath) -> cvl::rgb8_image;
void write_image_opencv(cv::Mat const& img, std::filesystem::path const& filepath);
void write_image(cvl::gray8_image const& img, std::filesystem::path const& filepath);

} // namespace utility

#endif
