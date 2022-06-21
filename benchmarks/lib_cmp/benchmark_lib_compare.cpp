#include "../utility/image_io.hpp"

#include <cvl/cvl.hpp>

#include <benchmark/benchmark.h>
#include <opencv2/imgproc.hpp>

#include <filesystem>

using namespace cvl::literals::integer_literals;

namespace {

const auto resource_dir = std::filesystem::path{"../resources"};
const auto filepath = resource_dir / "lenna.png";

} // namespace

static void lib_cmp_bgr2gray_opencv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    }
}
BENCHMARK(lib_cmp_bgr2gray_opencv);

static void lib_cmp_bgr2gray_cvl(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::color_convert(rgb_img, gray_img);
    }
}
BENCHMARK(lib_cmp_bgr2gray_cvl);

static void lib_cmp_minmax_opencv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);

    for (auto _ : state)
    {
        double min, max;
        cv::minMaxIdx(gray_img, &min, &max);
        benchmark::DoNotOptimize(min);
        benchmark::DoNotOptimize(max);
    }
}
BENCHMARK(lib_cmp_minmax_opencv);

static void lib_cmp_minmax_cvl(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);

    for (auto _ : state)
    {
        auto const result = cvl::minmax_value(gray_img);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(lib_cmp_minmax_cvl);

static void lib_cmp_minmaxloc_opencv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);

    for (auto _ : state)
    {
        double min, max;
        cv::Point min_loc;
        cv::Point max_loc;
        cv::minMaxLoc(gray_img, &min, &max, &min_loc, &max_loc);
        benchmark::DoNotOptimize(min);
        benchmark::DoNotOptimize(max);
        benchmark::DoNotOptimize(min_loc);
        benchmark::DoNotOptimize(max_loc);
    }
}
BENCHMARK(lib_cmp_minmaxloc_opencv);

static void lib_cmp_threshold_cvl_binary(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);
    auto gray_result_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::apply_threshold(gray_img, gray_result_img, 127_u8, cvl::threshold_binary_t{});
    }
}
BENCHMARK(lib_cmp_threshold_cvl_binary);

static void lib_cmp_threshold_cvl_binary_inv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);
    auto gray_result_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::apply_threshold(gray_img, gray_result_img, 127_u8, cvl::threshold_binary_inverse_t{});
    }
}
BENCHMARK(lib_cmp_threshold_cvl_binary_inv);

static void lib_cmp_threshold_cvl_trunc(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);
    auto gray_result_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::apply_threshold(gray_img, gray_result_img, 127_u8, cvl::threshold_truncate_t{});
    }
}
BENCHMARK(lib_cmp_threshold_cvl_trunc);

static void lib_cmp_threshold_cvl_tozero(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);
    auto gray_result_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::apply_threshold(gray_img, gray_result_img, 127_u8, cvl::threshold_to_zero_t{});
    }
}
BENCHMARK(lib_cmp_threshold_cvl_tozero);

static void lib_cmp_threshold_cvl_tozero_inv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image(filepath);
    auto gray_img = cvl::gray8_image{rgb_img.size()};
    cvl::color_convert(rgb_img, gray_img);
    auto gray_result_img = cvl::gray8_image{rgb_img.size()};

    for (auto _ : state)
    {
        cvl::apply_threshold(gray_img, gray_result_img, 127_u8, cvl::threshold_to_zero_inverse_t{});
    }
}
BENCHMARK(lib_cmp_threshold_cvl_tozero_inv);

static void lib_cmp_threshold_opencv_binary(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    auto gray_result_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(gray_img, gray_result_img, 127, 255, cv::THRESH_BINARY);
    }
}
BENCHMARK(lib_cmp_threshold_opencv_binary);

static void lib_cmp_threshold_opencv_binary_inv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    auto gray_result_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(gray_img, gray_result_img, 127, 255, cv::THRESH_BINARY_INV);
    }
}
BENCHMARK(lib_cmp_threshold_opencv_binary_inv);

static void lib_cmp_threshold_opencv_trunc(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    auto gray_result_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(gray_img, gray_result_img, 127, 255, cv::THRESH_TRUNC);
    }
}
BENCHMARK(lib_cmp_threshold_opencv_trunc);

static void lib_cmp_threshold_opencv_tozero(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    auto gray_result_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(gray_img, gray_result_img, 127, 255, cv::THRESH_TOZERO);
    }
}
BENCHMARK(lib_cmp_threshold_opencv_tozero);


static void lib_cmp_threshold_opencv_tozero_inv(benchmark::State& state)
{
    auto const rgb_img = utility::read_image_opencv(filepath);
    auto gray_img = cv::Mat{};
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);
    auto gray_result_img = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(gray_img, gray_result_img, 127, 255, cv::THRESH_TOZERO_INV);
    }
}
BENCHMARK(lib_cmp_threshold_opencv_tozero_inv);
