/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

#include <algorithm>
#include <complex>
#include <numeric>
#include <type_traits>

namespace fractals {
namespace mandelbrot
{
	using real_type = double;

	using iteration_type = decltype( MAX_CHANNEL_VALUE );
	using value_type = std::remove_const< iteration_type >::type;

	template < typename T = value_type >
	using container_type = matrix< T >;
	using index_type = container_type<>::index_type;

	value_type
	compute_iteration(
		const real_type c_real,
		const real_type c_imaginary,
		const value_type max_iterations )
	{
		const std::complex< real_type > c( c_real, c_imaginary );
		std::complex< real_type > z = 0.0;

		const auto bailout_coefficient = 2.0;

		value_type iteration;
		for ( iteration = 0; ( iteration < max_iterations ) && ( std::abs( z ) < bailout_coefficient ); ++iteration )
		{
			z = z * z + c;
		}

		return iteration;
	}

	real_type
	map_horizontal_pixel_to_real_value(
		const index_type column,
		const index_type columns,
		const real_type min_real,
		const real_type max_real )
	{
		const auto range = max_real - min_real;

		return column * ( range / columns ) + min_real;
	}

	real_type
	map_vertical_pixel_to_imaginary_value(
		const index_type row,
		const index_type rows,
		const real_type min_imaginary,
		const real_type max_imaginary )
	{
		const auto range = max_imaginary - min_imaginary;

		return row * ( range / rows ) + min_imaginary;
	}

	value_type
	compute_value(
		const index_type row,
		const index_type rows,
		const index_type column,
		const index_type columns,
		const value_type max_iterations,
		const real_type min_real,
		const real_type max_real,
		const real_type min_imaginary,
		const real_type max_imaginary )
	{
		const auto imaginary_value =
			map_vertical_pixel_to_imaginary_value(
				row,
				columns,
				min_imaginary,
				max_imaginary );

		const auto real_value =
			map_horizontal_pixel_to_real_value(
				column,
				rows,
				min_real,
				max_real );

		return
			compute_iteration(
				real_value,
				imaginary_value,
				max_iterations );
	}

	template < typename ValueMappingFunction >
	auto
	compute_buffer(
		const index_type rows,
		const index_type columns,
		const value_type max_iterations,
		const real_type min_real,
		const real_type max_real,
		const real_type min_imaginary,
		const real_type max_imaginary,
		ValueMappingFunction mapper )
	{
		using element_type = std::result_of< ValueMappingFunction( const value_type value ) >::type;

		container_type< element_type > set( rows, columns );

		for ( std::size_t row = 0; row < set.get_rows(); ++row )
		{
			for ( std::size_t column = 0; column < set.get_columns(); ++column )
			{
				set[row][column] =
					mapper(
						compute_value(
							row,
							rows,
							column,
							columns,
							max_iterations,
							min_real,
							max_real,
							min_imaginary,
							max_imaginary ));
			}
		}

		return set;
	}

	rgb_channels
	compute_color_map( const value_type value )
	{
		return
		{
			static_cast< channel_type >( value ), // Red
			static_cast< channel_type >( value * value ), // Green
			static_cast< channel_type >( value * std::abs( std::sin( value ) ) ) // Blue
		};
	}
}}