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
		rgb_image const & image )
	{
		auto writer =
			get_stream_writer(
				filename,
				format::ppm,
				encoding,
				image.size1(),
				image.size2() );

		for ( auto row = image.begin1(); row != image.end1(); ++row )
		{
			for ( auto column = row.begin(); column != row.end(); ++column )
			{
				const auto color = *column;

				writer << static_cast< unsigned int >( color.red ) << " ";
				writer << static_cast< unsigned int >( color.green ) << " ";
				writer << static_cast< unsigned int >( color.blue ) << " ";
			}

			writer << std::endl;
		}
	}
}