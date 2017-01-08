/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <memory>

template < typename T >
class matrix
{
public:
	using value_type = T;
	using container_type = std::unique_ptr< value_type[] >;
	using index_type = std::size_t;

	matrix(
		const index_type input_rows,
		const index_type input_columns ) :
		container( std::make_unique< value_type[] >( input_rows * input_columns ) ),
		rows( input_rows ),
		columns( input_columns )
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
		auto offset = row * columns;

		return &this->container[offset];
	}

	value_type const * const
	operator[]( const index_type row ) const
	{
		auto offset = row * columns;

		return &this->container[offset];
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

protected:
	container_type container;

	index_type rows;
	index_type columns;
};