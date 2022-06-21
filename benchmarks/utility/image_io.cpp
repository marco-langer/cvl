#include "image_io.hpp"

#include <fmt/core.h>
#include <opencv2/imgcodecs.hpp>

#include <stdexcept>

namespace {

void create_dir(std::filesystem::path const& dir)
{
    // TOCTOU but don't care as it is only a benchmark project
    if (std::filesystem::is_regular_file(dir))
    {
        throw std::runtime_error{
            fmt::format(
                "unable to create directory '{}', file already exists.",
                reinterpret_cast<const char *>(dir.u8string().c_str())
            )
        };
    }
    if (!std::filesystem::is_directory(dir))
    {
        std::filesystem::create_directories(dir);
    }
}

auto opencv_to_cvl(cv::Mat const& mat) -> cvl::rgb8_image
{
    using cv_pixel = cv::Point3_<std::uint8_t>;

    auto img = cvl::rgb8_image{mat.cols, mat.rows};
    for (auto first = img.begin(); cv_pixel& p : cv::Mat_<cv_pixel>(mat))
    {
        *first++ = cvl::rgb8_pixel{p.x, p.y, p.z};
    }

    return img;
}

auto cvl_to_opencv(cvl::gray8_image const& img) -> cv::Mat
{
    using cv_gray_pixel = std::uint8_t;

    auto view = img.view();
    cv::Mat mat(
        static_cast<int>(view.height()),
        static_cast<int>(view.width()),
        CV_8UC1
    );

    // TODO is this a deep copy of opencv mat just to get a range-based for loop?
    for (auto cvl_first = view.begin(); cv_gray_pixel& p : cv::Mat_<cv_gray_pixel>{mat})
    {
        auto value = *cvl_first++;
        p = value.get_c<0>();
    }

    return mat;
}

} // namespace

namespace utility {

auto read_image_opencv(std::filesystem::path const& filepath) -> cv::Mat
{
    if (!std::filesystem::is_regular_file(filepath))
    {
        throw std::runtime_error{
            fmt::format(
                "invalid filepath '{}'",
                reinterpret_cast<const char *>(filepath.u8string().c_str())
            )
        };
    }
    return cv::imread(filepath);
}

auto read_image(std::filesystem::path const& filepath) -> cvl::rgb8_image
{
    return opencv_to_cvl(read_image_opencv(filepath));
}

void write_image_opencv(cv::Mat const& img, std::filesystem::path const& filepath)
{
    create_dir(filepath.parent_path());
    cv::imwrite(filepath, img);
}

void write_image(cvl::gray8_image const& img, std::filesystem::path const& filepath)
{
    write_image_opencv(cvl_to_opencv(img), filepath);
}

} // namespace utility
