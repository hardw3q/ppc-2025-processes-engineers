#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace pankov_gauss_filter {

struct Image {
  int width = 0;
  int height = 0;
  int channels = 0;                // 1 (grayscale) or 3/4 (RGB/RGBA)
  std::vector<std::uint8_t> data;  // row-major: (y * width + x) * channels + c
};

using InType = Image;
using OutType = Image;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace pankov_gauss_filter
