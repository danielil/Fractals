/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

namespace fractals
{
	template < typename ValueType >
	rgb_channels
	map_color( const ValueType value )
	{
		return
		{
			static_cast< channel_type >( value ), // Red
			static_cast< channel_type >( value * value ), // Green
			static_cast< channel_type >( value * std::abs( std::sin( value ) ) ) // Blue
		};
	}
}