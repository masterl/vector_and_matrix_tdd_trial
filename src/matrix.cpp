#include "matrix.hpp"
#include <cmath>
#include <stdexcept>

#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

Matrix::Matrix( void )
    : _dimensions( std::make_pair( 0, 0 ) )
{
}

Matrix::Matrix( Matrix const &other )
    : _dimensions( std::make_pair( 0, 0 ) )
{
    reset_dimensions( other.dimensions().first, other.dimensions().second );

    for( position_t line = 0; line < _dimensions.first; ++line )
    {
        for( position_t column = 0; column < _dimensions.first; ++column )
        {
            ( *this )[line][column] = other[line][column];
        }
    }
}

void Matrix::set( std::initializer_list< value_t > values,
                  position_t const &lines,
                  position_t const &columns )
{
    typename std::initializer_list< value_t >::iterator it = values.begin();

    this->reset_dimensions( lines, columns );

    for( position_t i = 0; ( i < ( lines * columns ) ) && ( it != values.end() ); ++i )
    {
        ( *this )[0][i] = *it;
        ++it;
    }
}

Matrix Matrix::generate_minor( position_t const &line, position_t const &column ) const
{
    Matrix result;
    result.reset_dimensions( _dimensions.first - 1, _dimensions.second - 1 );
    position_t minor_pos = 0;

    for( position_t i = 0; i < _dimensions.first; ++i )
    {
        if( i == line )
        {
            continue;
        }

        for( position_t j = 0; j < _dimensions.second; ++j )
        {
            if( j == column )
            {
                continue;
            }

            result[0][minor_pos] = ( *this )[i][j];
            ++minor_pos;
        }
    }

    return result;
}

void Matrix::reset_dimensions( position_t const &lines, position_t const &columns )
{
    _data.reset( new value_t[lines * columns] );

    _dimensions.first = lines;
    _dimensions.second = columns;
}

MatrixDimensions Matrix::dimensions( void ) const
{
    return _dimensions;
}

value_t Matrix::determinant( void ) const
{
    value_t result = 0.0;

    if( _dimensions.first != _dimensions.second )
    {
        throw std::domain_error( "This class can only compute determinant for square matrixes!" );
    }

    switch( _dimensions.first )
    {
        case 1:
            result = ( *this )[0][0];
            break;
        case 2:
            result = ( *this )[0][0] * ( *this )[1][1];
            result -= ( *this )[1][0] * ( *this )[0][1];
            break;
        case 3:
            result = ( *this )[0][0] *
                     ( ( *this )[1][1] * ( *this )[2][2] - ( *this )[2][1] * ( *this )[1][2] );
            result -= ( *this )[0][1] *
                      ( ( *this )[1][0] * ( *this )[2][2] - ( *this )[2][0] * ( *this )[1][2] );
            result += ( *this )[0][2] *
                      ( ( *this )[1][0] * ( *this )[2][1] - ( *this )[2][0] * ( *this )[1][1] );
            break;
        default:
            result = inner_determinant( *this );
            break;
    }

    return result;
}

value_t Matrix::inner_determinant( Matrix const &matrix ) const
{
    value_t result = 0.0;
    position_t columns = matrix.dimensions().second;
    Matrix sub_matrix;

    if( ( matrix.dimensions().first == 1 ) && ( matrix.dimensions().second == 1 ) )
    {
        return matrix[0][0];
    }

    for( position_t column = 0; column < columns; ++column )
    {
        if( is_zero( matrix[0][column] ) )
        {
            continue;
        }

        sub_matrix = matrix.generate_minor( 0, column );

        if( ( column % 2 ) == 0 )
        {
            result += matrix[0][column] * inner_determinant( sub_matrix );
        }
        else
        {
            result -= matrix[0][column] * inner_determinant( sub_matrix );
        }
    }

    return result;
}

bool Matrix::is_zero( value_t const &value ) const
{
    value_t absolute = fabs( value );

    return ( absolute < 0.00001 );
}

void Matrix::assert_dimensions_match( Matrix const &other ) const
{
    MatrixDimensions other_dimensions;

    other_dimensions = other.dimensions();

    if( ( _dimensions.first != other_dimensions.first ) ||
        ( _dimensions.second != other_dimensions.second ) )
    {
        throw std::domain_error( "Matrix dimensions differ! Both matrixes should be NxM!" );
    }
}

Matrix Matrix::transposed( void ) const
{
    Matrix transposed;
    transposed.reset_dimensions( _dimensions.second, _dimensions.first );

    for( position_t i = 0; i < _dimensions.first; ++i )
    {
        for( position_t j = 0; j < _dimensions.second; ++j )
        {
            transposed[j][i] = ( *this )[i][j];
        }
    }

    return transposed;
}

Matrix &Matrix::transpose( void )
{
    ( *this ) = this->transposed();

    return ( *this );
}

Matrix Matrix::cofactor_matrix( void )
{
    Matrix cofactors;

    cofactors.reset_dimensions( _dimensions.first, _dimensions.second );

    for( position_t i = 0; i < _dimensions.first; ++i )
    {
        for( position_t j = 0; j < _dimensions.second; ++j )
        {
            cofactors[i][j] = this->generate_minor( i, j ).determinant();
            if( ( ( i + j ) % 2 ) == 1 )
            {
                cofactors[i][j] = -cofactors[i][j];
            }
        }
    }

    return cofactors;
}

Matrix Matrix::adjoint_matrix( void )
{
    return this->cofactor_matrix().transpose();
}

Matrix Matrix::generate_inverse( void )
{
    Matrix inverse_matrix;

    if( _dimensions.first != _dimensions.second )
    {
        throw std::domain_error( "Matrix should be square to have an inverse!" );
    }

    if( is_zero( this->determinant() ) )
    {
        throw std::domain_error(
            "Matrix's determinant should be different than 0 to have and inverse!" );
    }

    inverse_matrix = this->adjoint_matrix();

    return inverse_matrix / this->determinant();
}

Matrix Matrix::identity_matrix( position_t const &lines, position_t const &columns )
{
    Matrix identity;

    identity.reset_dimensions( lines, columns );

    for( position_t line = 0; line < lines; ++line )
    {
        for( position_t column = 0; column < columns; ++column )
        {
            if( line == column )
            {
                identity[line][column] = 1;
            }
            else
            {
                identity[line][column] = 0;
            }
        }
    }

    return identity;
}

value_t *Matrix::operator[]( int const &line )
{
    return _data.get() + ( line * _dimensions.second );
}

value_t const *Matrix::operator[]( int const &line ) const
{
    return _data.get() + ( line * _dimensions.second );
}

Matrix Matrix::operator*( Matrix const &other ) const
{
    Matrix result;
    MatrixDimensions other_dimensions;
    value_t sum;

    other_dimensions = other.dimensions();

    if( _dimensions.second != other_dimensions.first )
    {
        throw std::domain_error(
            "First matrix column count differs from second matrix lines count!" );
    }

    result.reset_dimensions( _dimensions.first, other_dimensions.second );

    for( position_t i = 0; i < _dimensions.first; ++i )
    {
        for( position_t j = 0; j < other_dimensions.second; ++j )
        {
            sum = 0.0;

            for( position_t k = 0; k < other_dimensions.second; ++k )
            {
                sum += ( *this )[i][k] * other[k][j];
            }

            result[i][j] = sum;
        }
    }

    return result;
}

Matrix Matrix::operator/( Matrix const &other ) const
{
    assert_dimensions_match( other );

    return iterate_with_other( other, []( value_t this_elem, value_t other_elem ) -> value_t {
        return this_elem / other_elem;
    } );
}

Matrix Matrix::operator+( Matrix const &other ) const
{
    assert_dimensions_match( other );

    return iterate_with_other( other, []( value_t this_elem, value_t other_elem ) -> value_t {
        return this_elem + other_elem;
    } );
}

Matrix Matrix::operator-( Matrix const &other ) const
{
    assert_dimensions_match( other );

    return iterate_with_other( other, []( value_t this_elem, value_t other_elem ) -> value_t {
        return this_elem - other_elem;
    } );
}

Matrix Matrix::operator*( value_t const &scalar ) const
{
    return derive_from_self(
        [scalar]( value_t const &this_elem ) -> value_t { return this_elem * scalar; } );
}

Matrix &Matrix::operator*=( value_t const &scalar )
{
    iterate_self( [scalar]( value_t &elem ) -> void { elem *= scalar; } );

    return *this;
}

Matrix Matrix::operator/( value_t const &scalar ) const
{
    return derive_from_self(
        [scalar]( value_t const &this_elem ) -> value_t { return this_elem / scalar; } );
}

Matrix &Matrix::operator/=( value_t const &scalar )
{
    iterate_self( [scalar]( value_t &elem ) -> void { elem /= scalar; } );

    return *this;
}

Matrix Matrix::operator+( value_t const &scalar ) const
{
    return derive_from_self(
        [scalar]( value_t const &this_elem ) -> value_t { return this_elem + scalar; } );
}

Matrix &Matrix::operator+=( value_t const &scalar )
{
    iterate_self( [scalar]( value_t &elem ) -> void { elem += scalar; } );

    return *this;
}

Matrix Matrix::operator-( value_t const &scalar ) const
{
    return derive_from_self(
        [scalar]( value_t const &this_elem ) -> value_t { return this_elem - scalar; } );
}

Matrix &Matrix::operator-=( value_t const &scalar )
{
    iterate_self( [scalar]( value_t &elem ) -> void { elem -= scalar; } );

    return *this;
}

Matrix &Matrix::operator=( Matrix const &other )
{
    reset_dimensions( other.dimensions().first, other.dimensions().second );

    for( position_t line = 0; line < _dimensions.first; ++line )
    {
        for( position_t column = 0; column < _dimensions.first; ++column )
        {
            ( *this )[line][column] = other[line][column];
        }
    }

    return *this;
}
