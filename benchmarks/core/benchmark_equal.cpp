#include <cvl/cvl.hpp>

#include <benchmark/benchmark.h>

#include <algorithm>

static void equal_std_vector(benchmark::State& state)
{
    auto const img1 = std::vector<std::uint16_t>(1024 * 1024);
    auto const img2 = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        auto result = std::equal(std::cbegin(img1), std::cend(img1), std::cbegin(img2));
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(equal_std_vector);

static void equal_std_pixel(benchmark::State& state)
{
    auto const img1 = cvl::gray16_image{{.width = 1024, .height = 1024}};
    auto const img2 = cvl::gray16_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        auto const result = std::equal(std::cbegin(img1), std::cend(img1), std::cbegin(img2));
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(equal_std_pixel);

static void equal_image_pixel(benchmark::State& state)
{
    auto const img1 = cvl::gray16_image{{.width = 1024, .height = 1024}};
    auto const img2 = cvl::gray16_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        auto const result = (img1 == img2);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(equal_image_pixel);
