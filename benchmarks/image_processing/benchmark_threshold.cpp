#include <cvl/cvl.hpp>
#include <cvl/image_processing/detail/threshold_naive.hpp>

#include <benchmark/benchmark.h>

#include <cstdint>
#include <vector>

using namespace cvl::literals::integer_literals;

static void threshold_binary_naive(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::apply_threshold_naive(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_binary_t{}
        );
    }
}
BENCHMARK(threshold_binary_naive);

static void threshold_binary(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::apply_threshold(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_binary_t{}
        );
    }
}
BENCHMARK(threshold_binary);

static void threshold_binary_inverse_naive(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::apply_threshold_naive(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_binary_inverse_t{}
        );
    }
}
BENCHMARK(threshold_binary_inverse_naive);

static void threshold_binary_inverse(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::apply_threshold(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_binary_inverse_t{}
        );
    }
}
BENCHMARK(threshold_binary_inverse);

static void threshold_truncate_naive(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::apply_threshold_naive(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_truncate_t{}
        );
    }
}
BENCHMARK(threshold_truncate_naive);

static void threshold_truncate(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::apply_threshold(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_truncate_t{}
        );
    }
}
BENCHMARK(threshold_truncate);

static void threshold_tozero_naive(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::apply_threshold_naive(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_to_zero_t{}
        );
    }
}
BENCHMARK(threshold_tozero_naive);

static void threshold_tozero(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::apply_threshold(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_to_zero_t{}
        );
    }
}
BENCHMARK(threshold_tozero);

static void threshold_tozero_inverse_naive(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::detail::apply_threshold_naive(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_to_zero_inverse_t{}
        );
    }
}
BENCHMARK(threshold_tozero_inverse_naive);

static void threshold_tozero_inverse(benchmark::State& state)
{
    auto const gray8_img = cvl::gray8_image{{.width = 1024, .height = 1024}};
    auto gray8_result_img = cvl::gray8_image{{.width = 1024, .height = 1024}};

    for (auto _ : state)
    {
        cvl::apply_threshold(
            gray8_img, gray8_result_img,
            127_u8, cvl::threshold_to_zero_inverse_t{}
        );
    }
}
BENCHMARK(threshold_tozero_inverse);
