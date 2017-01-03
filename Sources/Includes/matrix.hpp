/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <vector>

template < typename T >
class matrix
{
public:
	using value_type = T;
	using container_type = std::vector< value_type >;
	using index_type = std::size_t;

	constexpr matrix(
		const index_type rows,
		const index_type columns ) :
		elements( rows * columns ),
		rows( rows ),
		columns( columns )
	{
	}

	~matrix() noexcept = default;

	constexpr matrix( matrix const & other ) = default;
	constexpr matrix( matrix&& other ) noexcept = default;

	constexpr matrix& operator=( matrix const & rhs ) = default;
	constexpr matrix& operator=( matrix&& rhs ) noexcept = default;

	value_type*
	operator[]( const index_type row )
	{
		auto offset = row * columns;

		return this->elements.data() + offset;
	}

	constexpr index_type
	get_rows() const
	{
		return this->rows;
	}

	constexpr index_type
	get_columns() const
	{
		return this->columns;
	}

private:
	container_type elements;

	index_type rows;
	index_type columns;
};
