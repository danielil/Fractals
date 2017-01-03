/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

namespace fractals
{
	auto find_mandelbrot(
		const double c_real,
		const double c_imaginary,
		const std::size_t max_iterations )
	{
		const std::complex< double > c( c_real, c_imaginary );
		std::complex< double > z = 0;

		const auto bailout_coefficient = 2.0;

		std::size_t iteration;
		for ( iteration = 0; ( iteration < max_iterations ) && ( std::abs( z ) < bailout_coefficient ); ++iteration )
		{
			z = z * z + c;
		}

		return iteration;
	}

	double map_horizontal_pixel_to_real_value(
		const std::size_t column,
		const std::size_t columns,
		const double min_real,
		const double max_real )
	{
		const auto range = max_real - min_real;

		return column * ( range / columns ) + min_real;
	}

	double map_vertical_pixel_to_imaginary_value(
		const std::size_t row,
		const std::size_t rows,
		const double min_imaginary,
		const double max_imaginary )
	{
		const auto range = max_imaginary - min_imaginary;

		return row * ( range / rows ) + min_imaginary;
	}

	image_rgb compute_mandelbrot_buffer(
		const std::size_t rows,
		const std::size_t columns,
		const std::size_t max_iterations,
		const double min_real,
		const double max_real,
		const double min_imaginary,
		const double max_imaginary )
	{
		image_rgb image( rows, columns );

		for ( std::size_t row = 0; row < image.get_rows(); ++row )
		{
			for ( std::size_t column = 0; column < image.get_columns(); ++column )
			{
				const auto real_value = map_horizontal_pixel_to_real_value( column, rows, min_real, max_real );
				const auto imaginary_value = map_vertical_pixel_to_imaginary_value( row, columns, min_imaginary, max_imaginary );

				const auto iteration = find_mandelbrot( real_value, imaginary_value, max_iterations );

				image[row][column][RED] = static_cast< channel_depth >( iteration * iteration );
				image[row][column][GREEN] = static_cast< channel_depth >( iteration * iteration );
				image[row][column][BLUE] = static_cast< channel_depth >( iteration * std::abs( std::sin( iteration ) ) );
			}
		}

		return image;
	}
}