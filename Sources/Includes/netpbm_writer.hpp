/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

#include <fstream>
#include <functional>
#include <unordered_map>

namespace netpbm
{
	enum class format
	{
		// Portable BitMap
		pbm,
		// Portable GrayMap
		pgm,
		// Portable PixMap
		ppm
	};

	enum class encoding
	{
		ascii,
		binary
	};

	static const std::unordered_map< format, std::string > format_to_string
	{
		{ format::pbm, "pbm" },
		{ format::pgm, "pgm" },
		{ format::ppm, "ppm" }
	};

	static const std::unordered_map<
		format,
		std::unordered_map<
			encoding,
			unsigned int > > format_to_magic_number = 
	{
		{
			format::pbm,
			{
				{ encoding::ascii, 1 },
				{ encoding::binary, 4 }
			}
		},
		{
			format::pgm,
			{
				{ encoding::ascii, 2 },
				{ encoding::binary, 5 }
			}
		},
		{
			format::ppm,
			{
				{ encoding::ascii, 3 },
				{ encoding::binary, 6 }
			}
		}
	};

	std::ofstream
	get_stream_writer(
		const std::string filename,
		const format format,
		const encoding encoding,
		const std::size_t rows,
		const std::size_t columns )
	{
		std::ofstream output( filename + "." + format_to_string.at( format ) );
		const auto magic_number = format_to_magic_number.at( format ).at( encoding );

		output << "P" << magic_number << std::endl;
		output << rows << " " << columns << std::endl;

		if ( format != format::pbm )
		{
			output << static_cast< unsigned int >( MAX_CHANNEL_VALUE ) << std::endl;
		}

		return output;
	}

	void
	write(
		const std::string filename,
		const encoding encoding,
		binary_image const & buffer )
	{
		auto writer =
			get_stream_writer(
				filename,
				format::pbm,
				encoding,
				buffer.get_rows(),
				buffer.get_columns() );

		for ( binary_image::index_type row = 0; row < buffer.get_rows(); ++row )
		{
			for ( binary_image::index_type column = 0; column < buffer.get_columns(); ++column )
			{
				writer << static_cast< unsigned int >( buffer[row][column] ) << " ";
			}

			writer << std::endl;
		}
	}

	void
	write(
		const std::string filename,
		const encoding encoding,
		monochrome_image const & image )
	{
		auto writer =
			get_stream_writer(
				filename,
				format::pgm,
				encoding,
				image.get_rows(),
				image.get_columns() );

		for ( monochrome_image::index_type row = 0; row < image.get_rows(); ++row )
		{
			for ( monochrome_image::index_type column = 0; column < image.get_columns(); ++column )
			{
				writer << static_cast< unsigned int >( image[row][column] ) << " ";
			}

			writer << std::endl;
		}
	}

	void
	write(
		const std::string filename,
		const encoding encoding,
		rgb_image const & image )
	{
		auto writer =
			get_stream_writer(
				filename,
				format::ppm,
				encoding,
				image.get_rows(),
				image.get_columns() );

		for ( rgb_image::index_type row = 0; row < image.get_rows(); ++row )
		{
			for ( rgb_image::index_type column = 0; column < image.get_columns(); ++column )
			{
				const auto color = image[row][column];

				writer << static_cast< unsigned int >( color.red ) << " ";
				writer << static_cast< unsigned int >( color.green ) << " ";
				writer << static_cast< unsigned int >( color.blue ) << " ";
			}

			writer << std::endl;
		}
	}
}