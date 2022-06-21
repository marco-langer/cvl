#include <cvl/cvl.hpp>

#include <benchmark/benchmark.h>

#include <algorithm>

static void minmax_std_vector_cvl_max(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = cvl::detail::max_value(
            std::cbegin(uint16_vec), std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_cvl_max);

static void minmax_std_vector_std_max(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::max_element(
            std::cbegin(uint16_vec), std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_max);

static void minmax_std_vector_std_ranges_max(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::ranges::max_element(uint16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_ranges_max);

static void minmax_std_vector_pixel_cvl_max(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = cvl::detail::max_value(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_cvl_max);

static void minmax_std_vector_pixel_std_max(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::max_element(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_max);

#if 0
static void minmax_std_vector_pixel_std_ranges_max(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::ranges::max_element(gray16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_ranges_max);
#endif

static void minmax_image_pixel_max(benchmark::State& state)
{
    auto const gray16_img = cvl::gray16_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        auto const result = cvl::max_value(gray16_img);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_image_pixel_max);

static void minmax_std_vector_cvl_min(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = cvl::detail::min_value(
            std::cbegin(uint16_vec),
            std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_cvl_min);

static void minmax_std_vector_std_min(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::min_element(
            std::cbegin(uint16_vec),
            std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_min);

static void minmax_std_vector_std_ranges_min(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::ranges::min_element(uint16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_ranges_min);

static void minmax_std_vector_pixel_cvl_min(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = cvl::detail::min_value(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_cvl_min);

static void minmax_std_vector_pixel_std_min(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::min_element(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_min);

#if 0
static void minmax_std_vector_pixel_std_ranges_min(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = *std::ranges::min_element(gray16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_ranges_min);
#endif

static void minmax_image_pixel_min(benchmark::State& state)
{
    auto const gray16_img = cvl::gray16_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        auto const result = cvl::min_value(gray16_img);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_image_pixel_min);

static void minmax_std_vector_cvl_minmax(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);
    for (auto _ : state)
    {
        auto const result = cvl::detail::minmax_value(
            std::cbegin(uint16_vec),
            std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_cvl_minmax);

static void minmax_std_vector_std_minmax(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);
    for (auto _ : state)
    {
        auto const result = std::minmax_element(
            std::cbegin(uint16_vec),
            std::cend(uint16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_minmax);

static void minmax_std_vector_std_ranges_minmax(benchmark::State& state)
{
    auto const uint16_vec = std::vector<std::uint16_t>(1024 * 1024);
    for (auto _ : state)
    {
        auto const result = std::ranges::minmax_element(uint16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_std_ranges_minmax);

static void minmax_std_vector_pixel_cvl_minmax(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = cvl::detail::minmax_value(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_cvl_minmax);

static void minmax_std_vector_pixel_std_minmax(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = std::minmax_element(
            std::cbegin(gray16_vec),
            std::cend(gray16_vec)
        );
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_minmax);

#if 0
static void minmax_std_vector_pixel_std_ranges_minmax(benchmark::State& state)
{
    auto const gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        auto const result = std::ranges::minmax_element(gray16_vec);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_std_vector_pixel_std_ranges_minmax);
#endif

static void minmax_image_pixel_minmax(benchmark::State& state)
{
    auto const gray16_img = cvl::gray16_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        auto const result = cvl::minmax_value(gray16_img);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(minmax_image_pixel_minmax);
