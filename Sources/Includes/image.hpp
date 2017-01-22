/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <boost/numeric/ublas/matrix.hpp>

template< typename T >
using image_container = boost::numeric::ublas::matrix< T >;

using binary_image = image_container< bool >;

using channel_type = std::uint8_t;
using monochrome_image = image_container< channel_type >;

struct rgb_channels
{
	channel_type red = 0;
	channel_type green = 0;
	channel_type blue = 0;
};
using rgb_image = image_container< rgb_channels >;

static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();