/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

#include <algorithm>
#include <complex>
#include <numeric>

namespace fractals
{
	using real_type = double;
	using mandelbrot_type = std::size_t;

	auto
	compute_mandelbrot_iteration(
		const real_type c_real,
		const real_type c_imaginary,
		const std::size_t max_iterations )
	{
		const std::complex< real_type > c( c_real, c_imaginary );
		std::complex< real_type > z = 0.0;

		const auto bailout_coefficient = 2.0;

		mandelbrot_type iteration;
		for ( iteration = 0; ( iteration < max_iterations ) && ( std::abs( z ) < bailout_coefficient ); ++iteration )
		{
			z = z * z + c;
		}

		return iteration;
	}

	auto
	map_horizontal_pixel_to_real_value(
		const std::size_t column,
		const std::size_t columns,
		const real_type min_real,
		const real_type max_real )
	{
		const auto range = max_real - min_real;

		return column * ( range / columns ) + min_real;
	}

	auto
	map_vertical_pixel_to_imaginary_value(
		const std::size_t row,
		const std::size_t rows,
		const real_type min_imaginary,
		const real_type max_imaginary )
	{
		const auto range = max_imaginary - min_imaginary;

		return row * ( range / rows ) + min_imaginary;
	}

	auto
	compute_mandelbrot_buffer(
		const std::size_t rows,
		const std::size_t columns,
		const std::size_t max_iterations,
		const real_type min_real,
		const real_type max_real,
		const real_type min_imaginary,
		const real_type max_imaginary )
	{
		matrix< mandelbrot_type > set( rows, columns );

		for ( std::size_t row = 0; row < set.get_rows(); ++row )
		{
			const auto imaginary_value =
				map_vertical_pixel_to_imaginary_value(
					row,
					columns,
					min_imaginary,
					max_imaginary );

			for ( std::size_t column = 0; column < set.get_columns(); ++column )
			{
				const auto real_value =
					map_horizontal_pixel_to_real_value(
						column,
						rows,
						min_real,
						max_real );

				const auto iteration =
					compute_mandelbrot_iteration(
						real_value,
						imaginary_value,
						max_iterations );

				set[row][column] = iteration;
			}
		}

		return set;
	}

	template < typename Set >
	auto
	retrieve_mandelbrot_image( Set&& set )
	{
		image image( set.get_rows(), set.get_columns() );

		for ( std::size_t row = 0; row < image.get_rows(); ++row )
		{
			for ( std::size_t column = 0; column < image.get_columns(); ++column )
			{
				const auto value = set[row][column];

				image[row][column][RED] = static_cast< channel_depth >( value );
				image[row][column][GREEN] = static_cast< channel_depth >( value * value );
				image[row][column][BLUE] = static_cast< channel_depth >( value * std::abs( std::sin( value ) ) );
			}
		}

		return image;
	}
}