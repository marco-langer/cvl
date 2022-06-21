#include <cvl/cvl.hpp>
#include <cvl/image_processing/detail/threshold_naive.hpp>

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

using namespace cvl::literals::integer_literals;

namespace cvl {

auto operator<<(std::ostream& os, gray8_pixel const& p) -> std::ostream&
{
    return os << static_cast<int>(p.get_c<0>());
}

} // namespace cvl

TEST_CASE("image_processing.threshold.binary")
{
    auto const input_data = std::vector<cvl::gray8_pixel>
    {
        123_u8, 65_u8, 11_u8, 0_u8,
        222_u8, 55_u8, 255_u8, 0_u8,
        78_u8, 128_u8, 99_u8, 1_u8,
        127_u8, 127_u8, 12_u8, 254_u8
    };
    auto const expected_data = std::vector<std::uint8_t>
    {
        0_u8, 0_u8, 0_u8, 0_u8,
        255_u8, 0_u8, 255_u8, 0_u8,
        0_u8, 255_u8, 0_u8, 0_u8,
        255_u8, 255_u8, 0_u8, 255_u8
    };

    // TODO C++23 zip range
    auto const img = [&]()
    {
        auto tmp_img = cvl::gray8_image{{.width = 4, .height = 4}};
        for (auto i = 0_uz; auto&& p : tmp_img)
        {
            p = input_data[i++];
        }
        return tmp_img;
    }();

    auto result_img_naive = cvl::gray8_image{img.size()};
    auto result_img = cvl::gray8_image{img.size()};

    REQUIRE_NOTHROW(cvl::detail::apply_threshold_naive(img, result_img_naive, 127_u8, cvl::threshold_binary_t{}));
    REQUIRE_NOTHROW(cvl::apply_threshold(img, result_img, 127_u8, cvl::threshold_binary_t{}));

    // TODO C++23 zip range
    for (auto i = 0_uz; auto&& p : result_img_naive)
    {
        REQUIRE(p ==  expected_data[i++]);
    }
    REQUIRE(result_img_naive == result_img);
}

TEST_CASE("image_processing.threshold.binary inverse")
{
    auto const input_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254
    };
    auto const expected_data = std::vector<std::uint8_t>
    {
        255, 255, 255, 255,
        0, 255, 0, 255,
        255, 0, 255, 255,
        0, 0, 255, 0
    };

    // TODO C++23 zip range
    auto const img = [&]()
    {
        auto tmp_img = cvl::gray8_image{{.width = 4, .height = 4}};
        for (auto i = 0_uz; auto&& p : tmp_img)
        {
            p = cvl::gray8_pixel{input_data[i++]};
        }
        return tmp_img;
    }();

    auto result_img = cvl::gray8_image{img.size()};

    REQUIRE_NOTHROW(cvl::apply_threshold(img, result_img, 127_u8, cvl::threshold_binary_inverse_t{}));

    // TODO C++23 zip range
    for (auto i = 0_uz; auto&& p : result_img)
    {
        REQUIRE(p ==  cvl::gray8_pixel{expected_data[i++]});
    }
}

TEST_CASE("image_processing.threshold.truncate")
{
    auto const input_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254
    };
    auto const expected_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        127, 55, 127, 0,
        78, 127, 99, 1,
        127, 127, 12, 127
    };

    // TODO C++23 zip range
    auto const img = [&]()
    {
        auto tmp_img = cvl::gray8_image{{.width = 4, .height = 4}};
        for (auto i = 0_uz; auto&& p : tmp_img)
        {
            p = cvl::gray8_pixel{input_data[i++]};
        }
        return tmp_img;
    }();

    auto result_img = cvl::gray8_image{img.size()};

    REQUIRE_NOTHROW(cvl::apply_threshold(img, result_img, 127_u8, cvl::threshold_truncate_t{}));

    // TODO C++23 zip range
    for (auto i = 0_uz; auto&& p : result_img)
    {
        REQUIRE(p ==  cvl::gray8_pixel{expected_data[i++]});
    }
}

TEST_CASE("image_processing.threshold.to zero")
{
    auto const input_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254
    };
    auto const expected_data = std::vector<std::uint8_t>
    {
        0, 0, 0, 0,
        222, 0, 255, 0,
        0, 128, 0, 0,
        127, 127, 0, 254
    };

    // TODO C++23 zip range
    auto const img = [&]()
    {
        auto tmp_img = cvl::gray8_image{{.width = 4, .height = 4}};
        for (auto i = 0_uz; auto&& p : tmp_img)
        {
            p = cvl::gray8_pixel{input_data[i++]};
        }
        return tmp_img;
    }();

    auto result_img = cvl::gray8_image{img.size()};

    REQUIRE_NOTHROW(cvl::apply_threshold(img, result_img, 127_u8, cvl::threshold_to_zero_t{}));

    // TODO C++23 zip range
    for (auto i = 0_uz; auto&& p : result_img)
    {
        REQUIRE(p ==  cvl::gray8_pixel{expected_data[i++]});
    }
}

TEST_CASE("image_processing.threshold.to zero inverse")
{
    auto const input_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254
    };
    auto const expected_data = std::vector<std::uint8_t>
    {
        123, 65, 11, 0,
        0, 55, 0, 0,
        78, 0, 99, 1,
        0, 0, 12, 0
    };

    // TODO C++23 zip range
    auto const img = [&]()
    {
        auto tmp_img = cvl::gray8_image{{.width = 4, .height = 4}};
        for (auto i = 0_uz; auto&& p : tmp_img)
        {
            p = cvl::gray8_pixel{input_data[i++]};
        }
        return tmp_img;
    }();

    auto result_img = cvl::gray8_image{img.size()};

    REQUIRE_NOTHROW(cvl::apply_threshold(img, result_img, 127_u8, cvl::threshold_to_zero_inverse_t{}));

    // TODO C++23 zip range
    for (auto i = 0_uz; auto&& p : result_img)
    {
        REQUIRE(p ==  cvl::gray8_pixel{expected_data[i++]});
    }
}
