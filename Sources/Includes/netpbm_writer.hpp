/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image.hpp"

#include <fstream>
#include <unordered_map>
#include <future>

namespace netpbm
{
	enum class format
	{
		pbm,
		pgm,
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

	void
	write_metadata(
		std::ofstream & output,
		const unsigned int magic_number,
		const std::size_t rows,
		const std::size_t columns )
	{
		output << "P" << magic_number << std::endl;
		output << rows << " " << columns << std::endl;
		output << static_cast< unsigned int >( std::numeric_limits< channel_depth >::max() ) << std::endl;
	}

	void
	write(
		const std::string filename,
		const format format,
		const encoding encoding,
		image_rgb & buffer )
	{
		std::ofstream output( filename + "." + format_to_string.at( format ) );
		const auto magic_number = format_to_magic_number.at( format ).at( encoding );

		write_metadata(
			output,
			magic_number,
			buffer.get_rows(),
			buffer.get_columns() );

		for ( std::size_t row = 0; row < buffer.get_rows(); ++row )
		{
			for ( std::size_t column = 0; column < buffer.get_columns(); ++column )
			{
				for ( std::size_t channel = 0; channel < RGB_CHANNELS; ++channel )
				{
					output << static_cast< unsigned int >( buffer[row][column][channel] ) << " ";
				}
			}

			output << std::endl;
		}
	}
}
