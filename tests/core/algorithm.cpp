#include <cvl/cvl.hpp>

#include <catch2/catch_test_macros.hpp>

#include <numeric>

TEST_CASE("core.algorithm.max_value()")
{
    cvl::gray16_image img(4, 4);

    for (std::uint16_t i = 0; auto&& p : img)
    {
      p = cvl::gray16_pixel{i++};
    }

    REQUIRE_NOTHROW(cvl::max_value(img) == cvl::gray16_pixel{std::uint16_t{15}});
}
