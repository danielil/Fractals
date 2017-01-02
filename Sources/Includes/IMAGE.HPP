#pragma once

#include "matrix.hpp"

#include <array>

using image_binary = matrix< bool >;

using channel_depth = std::uint8_t;
using image_greyscale = matrix< channel_depth >;

static constexpr std::size_t RGB_CHANNELS = 3;
using rgb_container = std::array< channel_depth, RGB_CHANNELS >;
using image_rgb = matrix< rgb_container >;

static constexpr std::size_t RED = 0;
static constexpr std::size_t GREEN = 1;
static constexpr std::size_t BLUE = 2;