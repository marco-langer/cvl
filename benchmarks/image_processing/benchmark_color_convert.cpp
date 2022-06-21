#include <cvl/cvl.hpp>
#include <cvl/image_processing/detail/color_convert_naive.hpp>

#include <benchmark/benchmark.h>

#include <cstdint>
#include <vector>

static void color_convert_std_vector(benchmark::State& state)
{
    auto const rgb_img = std::vector<std::uint8_t>(1024 * 1024 * 3);
    auto gray_img = std::vector<std::uint8_t>(1024 * 1024);

    for (auto _ : state)
    {
        for (auto i = 0ull, j = 0ull; i < rgb_img.size(); i += 3, ++j)
        {
            gray_img[j] = static_cast<std::uint8_t>(
                0.299 * rgb_img[i]
                + 0.587 * rgb_img[i + 1]
                + 0.114 * rgb_img[i + 2]
            );
        }
    }
}
BENCHMARK(color_convert_std_vector);

static void color_convert_clv_naive(benchmark::State& state)
{
    auto const rgb_img = cvl::rgb8_image{{.width = 1024, .height = 1024}};
    auto gray_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::color_convert_naive(rgb_img, gray_img);
    }
}
BENCHMARK(color_convert_clv_naive);

static void color_convert_clv(benchmark::State& state)
{
    auto const rgb_img = cvl::rgb8_image{{.width = 1024, .height = 1024}};
    auto gray_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::color_convert(rgb_img, gray_img);
    }
}
BENCHMARK(color_convert_clv);
