/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "mandelbrot_generator.hpp"

#include "netpbm_writer.hpp"

#include <chrono>
#include <iostream>

int main()
{
	const std::string filename = "output_image";
	const std::size_t rows = 1024;
	const std::size_t columns = 1024;
	const auto max_iterations = MAX_CHANNEL_VALUE;
	const auto min_real = -1.5;
	const auto max_real = 0.7;
	const auto min_complex = -1.0;
	const auto max_complex = 1.0;

	const auto start = std::chrono::system_clock::now();

	auto mandelbrot_color_image =
		fractals::mandelbrot::compute_color_buffer(
			rows,
			columns,
			max_iterations,
			min_real,
			max_real,
			min_complex,
			max_complex );

	const auto end_calculation = std::chrono::system_clock::now();
	const std::chrono::duration< double > elapsed_seconds_calc = end_calculation - start;

	std::cout << "Calculation: " << elapsed_seconds_calc.count() << "s" << std::endl;

	netpbm::write(
		filename,
		netpbm::encoding::ascii,
		mandelbrot_color_image );

	const auto end_write = std::chrono::system_clock::now();
	const std::chrono::duration< double > elapsed_seconds_write = end_write - end_calculation;

	std::cout << "Write: " << elapsed_seconds_write.count() << "s" << std::endl;

	return 0;
}