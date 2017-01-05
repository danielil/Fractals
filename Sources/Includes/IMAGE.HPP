/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "matrix.hpp"

#include <array>

using channel_depth = std::uint8_t;
static constexpr std::size_t RGB_CHANNELS = 3;

using rgb_container = std::array< channel_depth, RGB_CHANNELS >;
using image = matrix< rgb_container >;

static constexpr std::size_t RED = 0;
static constexpr std::size_t GREEN = 1;
static constexpr std::size_t BLUE = 2;