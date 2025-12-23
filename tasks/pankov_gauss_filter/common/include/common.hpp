#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace pankov_gauss_filter {

struct Image {
  int width = 0;
  int height = 0;
  int channels = 0;
  std::vector<std::uint8_t> data;

  Image() = default;

  Image(int w, int h, int ch, std::vector<std::uint8_t> d) : width(w), height(h), channels(ch), data(std::move(d)) {}
};

using InType = Image;
using OutType = Image;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace pankov_gauss_filter
