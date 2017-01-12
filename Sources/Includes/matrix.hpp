/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <valarray>
#include <array>

template< typename T >
class iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;

    iterator(
		T* input_container,
		std::slice input_slice ) :
		container( input_container ),
		slice( input_slice )
	{
	}

    iterator(iterator const & it ) = default;

	void
	swap(iterator& it)
	{
		std::swap( this->container, it.container );
	}

    iterator&
	operator++()
	{
		++position;

		return *this;
	}

    iterator
	operator++( int )
	{
		const iterator iterator( *this );
		++( *this );

		return iterator;
	}

    iterator&
	operator--()
	{
		--position;

		return *this;
	}

    iterator
	operator--( int )
	{
		const iterator iterator( *this );
		--( *this );

		return iterator;
	}

    reference
	operator*() const
	{
		return this->ref( this->position );
	}

    reference
	operator[]( std::size_t idx )
	{
		return this->ref( idx );
	}

	bool
	operator==(iterator const & it ) const
	{
		return ( this == *it );
	}

	bool
	operator!=(iterator const & it ) const
	{
		return !( *this == it );
	}

private:

    reference ref( std::size_t idx )
	{
		return (*this->container)[this->slice.start() + idx * this->slice.stride()];
	}

	T* container;
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

    iterator< T >
	operator[]( const index_type row )
	{
		return iterator< T >( std::addressof( this->container[0] ), std::slice( row * this->rows, this->rows, 1 ) );
	}

    iterator< T >
	operator[]( const index_type row ) const
	{
        return iterator< T >( std::addressof( this->container[0] ), std::slice(row * this->rows, this->rows, 1));
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