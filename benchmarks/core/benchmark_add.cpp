#include <cvl/cvl.hpp>

#include <benchmark/benchmark.h>

#include <algorithm>
#include <functional>
#include <ranges>

using namespace cvl::literals::integer_literals;

static void add_std_loop(benchmark::State& state)
{
    auto uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        for (auto&& p : uint16_vec)
        {
            p += 1;
        }
    }
}
BENCHMARK(add_std_loop);

static void add_std_transform(benchmark::State& state)
{
    auto uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return p + 1_u16;
    };

    for (auto _ : state)
    {
        std::transform(
            std::cbegin(uint16_vec), std::cend(uint16_vec),
            std::begin(uint16_vec), op
        );
    }
}
BENCHMARK(add_std_transform);

static void add_std_ranges_transform(benchmark::State& state)
{
    auto uint16_vec = std::vector<std::uint16_t>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return p + 1_u16;
    };

    for (auto _ : state)
    {
        std::ranges::transform(uint16_vec, std::begin(uint16_vec), op);
    }
}
BENCHMARK(add_std_ranges_transform);

static void add_std_loop_copy(benchmark::State& state)
{
    auto const uint16_vec1 = std::vector<std::uint16_t>(1024 * 1024);
    auto uint16_vec2 = std::vector<std::uint16_t>(1024 * 1024);

    for (auto _ : state)
    {
        for (auto i = 0ull; i < uint16_vec1.size(); ++i)
        {
            uint16_vec2[i] = uint16_vec1[i] + 1;
        }
    }
}
BENCHMARK(add_std_loop_copy);

static void add_std_transform_copy(benchmark::State& state)
{
    auto const uint16_vec1 = std::vector<std::uint16_t>(1024 * 1024);
    auto uint16_vec2 = std::vector<std::uint16_t>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return p + 1_u16;
    };

    for (auto _ : state)
    {
        std::transform(
            std::cbegin(uint16_vec1), std::cend(uint16_vec1),
            std::begin(uint16_vec2), op
        );
    }
}
BENCHMARK(add_std_transform_copy);

static void add_std_transform_ranges_copy(benchmark::State& state)
{
    auto const uint16_vec1 = std::vector<std::uint16_t>(1024 * 1024);
    auto uint16_vec2 = std::vector<std::uint16_t>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return p + 1_u16;
    };

    for (auto _ : state)
    {
        std::ranges::transform(uint16_vec1, std::begin(uint16_vec2), op);
    }
}
BENCHMARK(add_std_transform_ranges_copy);

static void add_pixel_add(benchmark::State& state)
{
    auto gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    for (auto _ : state)
    {
        for (auto&& p : gray16_vec)
        {
            p += cvl::gray16_pixel{1_u16};
        }
    }
}
BENCHMARK(add_pixel_add);

static void add_pixel_std_transform_add(benchmark::State& state)
{
    auto gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return p + cvl::gray16_pixel{1_u16};
    };

    for (auto _ : state)
    {
        std::transform(
            std::cbegin(gray16_vec), std::cend(gray16_vec),
            std::begin(gray16_vec), op
        );
    }
}
BENCHMARK(add_pixel_std_transform_add);

static void add_pixel_std_transform_std_plus(benchmark::State& state)
{
    auto gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return std::plus<>{}(p, cvl::gray16_pixel{1_u16});
    };

    for (auto _ : state)
    {
        std::transform(
            std::cbegin(gray16_vec), std::cend(gray16_vec),
            std::begin(gray16_vec), op
        );
    }
}
BENCHMARK(add_pixel_std_transform_std_plus);

static void add_pixel_std_ranges_transform_std_plus(benchmark::State& state)
{
    auto gray16_vec = std::vector<cvl::gray16_pixel>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return std::plus<>{}(p, cvl::gray16_pixel{1_u16});
    };

    for (auto _ : state)
    {
        std::ranges::transform(gray16_vec, std::begin(gray16_vec), op);
    }
}
BENCHMARK(add_pixel_std_ranges_transform_std_plus);

static void add_pixel_transform_std_copy_plus(benchmark::State& state)
{
    auto const gray16_vec1 = std::vector<cvl::gray16_pixel>(1024 * 1024);
    auto gray16_vec2 = std::vector<cvl::gray16_pixel>(1024 * 1024);

    auto op = [](auto&& p)
    {
        return std::plus<>{}(p, cvl::gray16_pixel{1_u16});
    };

    for (auto _ : state)
    {
        std::transform(
            std::cbegin(gray16_vec1), std::cend(gray16_vec1),
            std::begin(gray16_vec2), op
        );
    }
}
BENCHMARK(add_pixel_transform_std_copy_plus);

static void add_pixel_transform_pixels(benchmark::State& state)
{
    auto gray16_img = cvl::gray16_image{{.width = 1024, .height = 1024}};

    auto op = [](auto&& p)
    {
        return std::plus<>{}(p, cvl::gray16_pixel{1_u16});
    };

    for (auto _ : state)
    {
        cvl::transform_pixels(gray16_img, gray16_img, op);
    }
}
BENCHMARK(add_pixel_transform_pixels);

static void add_pixel_transform_pixels_copy(benchmark::State& state)
{
    auto const gray16_img1 = cvl::gray16_image{{.width = 1024, .height = 1024}};
    auto gray16_img2 = cvl::gray16_image{{.width = 1024, .height = 1024}};

    auto op = [](auto&& p)
    {
        return std::plus<>{}(p, cvl::gray16_pixel{1_u16});
    };

    for (auto _ : state)
    {
        cvl::transform_pixels(gray16_img1, gray16_img2, op);
    }
}
BENCHMARK(add_pixel_transform_pixels_copy);
