#pragma once

#include <vector>

template < typename T >
class matrix
{
public:
	using value_type = T;
	using container_type = std::vector< value_type >;
	using index_type = std::size_t;

	matrix(
		const index_type rows,
		const index_type columns ) :
		elements( rows * columns ),
		rows( rows ),
		columns( columns )
	{
	}

	matrix(
		const index_type rows,
		const index_type columns,
		const value_type default_value ) :
		elements( rows * columns, default_value ),
		rows( rows ),
		columns( columns )
	{
	}

	~matrix() noexcept = default;

	matrix( matrix const & other ) = default;
	matrix( matrix&& other ) noexcept = default;

	matrix& operator=( matrix const & rhs ) = default;
	matrix& operator=( matrix&& rhs ) noexcept = default;

	value_type*
	operator[]( const index_type row )
	{
		const auto offset = row * columns;

		return this->elements.data() + offset;
	}

	index_type
	get_rows() const
	{
		return this->rows;
	}

	index_type
	get_columns() const
	{
		return this->columns;
	}

private:
	container_type elements;

	index_type rows = 0;
	index_type columns = 0;
};