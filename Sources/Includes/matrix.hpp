/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <valarray>

template< typename T >
class row_iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	row_iterator(T const * const input_element) :
		element(input_element)
	{
	}

	row_iterator(row_iterator const & it) :
		element(it.element)
	{
	}

	void
	swap(row_iterator& it)
	{
		std::swap(this->element, it.element);
	}

	row_iterator&
	operator++()
	{
		++position;

		return *this;
	}

	row_iterator
	operator++(int)
	{
		const row_iterator iterator(*this);
		++(*this);

		return iterator;
	}

	row_iterator&
	operator--()
	{
		--position;

		return *this;
	}

	row_iterator
	operator--(int)
	{
		const row_iterator iterator(*this);
		--(*this);

		return iterator;
	}

	reference
	operator*() const
	{
		return this->node->item;
	}

	bool
	operator==(row_iterator const & it) const
	{
		return ( *this == *it );
	}

	bool
	operator!=(row_iterator const & it) const
	{
		return !(*this == it);
	}

private:

	reference ref( std::size_t idx) const
	{
		return element[slice.start() + idx * slice.stride()];
	}

	std::valarray< T >* element = nullptr;
	std::slice slice;
	std::size_t position = 0;
};

template < typename T >
class matrix
{
public:
	using value_type = T;
	using container_type = std::valarray< value_type >;
	using index_type = std::size_t;

	matrix(
		const index_type input_rows,
		const index_type input_columns ) :
		container( input_rows * input_columns ),
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

	value_type const *
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