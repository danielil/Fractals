/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "matrix.hpp"

#include <numeric>

using binary_image = matrix< bool >;

using channel_type = std::uint8_t;
using monochrome_image = matrix< channel_type >;

struct rgb_channels
{
	channel_type red = 0;
	channel_type green = 0;
	channel_type blue = 0;
};
using rgb_image = matrix< rgb_channels >;

static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();