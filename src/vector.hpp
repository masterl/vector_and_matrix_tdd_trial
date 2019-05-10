#ifndef FIXED_VECTOR_H
#define FIXED_VECTOR_H

#include <array>
#include <cmath>
#include <initializer_list>
#include <type_traits>

typedef unsigned int position_t;

template < position_t DIMENSIONS, typename Scalar >
class Vector
{
    public:
    Vector< DIMENSIONS, Scalar >( void )
    {
        _coordinates.fill( 0.0 );
    }

    Vector< DIMENSIONS, Scalar >( std::initializer_list< Scalar > values )
    {
        this->set( values );
    }

    inline position_t dimensions( void ) const
    {
        return _coordinates.size();
    }

    Scalar distance_to( Vector< DIMENSIONS, Scalar > const &other ) const
    {
        Scalar distance = 0.0;
        Scalar diff;

        for( position_t i = 0; i < _coordinates.size(); ++i )
        {
            diff = _coordinates[i];
            diff -= other._coordinates[i];

            distance += diff * diff;
        }

        return sqrt( distance );
    }

    Scalar dot( Vector< DIMENSIONS, Scalar > const &other ) const
    {
        Scalar product = 0.0;

        for( position_t i = 0; i < _coordinates.size(); ++i )
        {
            product += _coordinates[i] * other._coordinates[i];
        }

        return product;
    }

    Scalar cross( Vector< 2, Scalar > const &other ) const
    {
        Scalar product = 0.0;

        product = _coordinates[0] * other._coordinates[1];
        product -= _coordinates[1] * other._coordinates[0];

        return product;
    }

    Vector< 3, Scalar > cross( Vector< 3, Scalar > const &other ) const
    {
        Vector< 3, Scalar > result;
        Scalar up, down;

        const position_t size = _coordinates.size();

        for( position_t i = 0; i < size; ++i )
        {
            down = _coordinates[( i + 1 ) % size] * other._coordinates[( i + 2 ) % size];
            up = _coordinates[( i + 2 ) % size] * other._coordinates[( i + 1 ) % size];

            result[i] = down - up;
        }

        return result;
    }

    void set( std::initializer_list< Scalar > values )
    {
        typename std::initializer_list< Scalar >::iterator it = values.begin();

        for( position_t i = 0; ( i < _coordinates.size() ) && ( it != values.end() ); ++i )
        {
            _coordinates[i] = *it;
            ++it;
        }
    }

    Scalar &operator[]( position_t const &position )
    {
        return _coordinates.at( position );
    }

    Scalar const &operator[]( position_t const &position ) const
    {
        return _coordinates.at( position );
    }

    Scalar operator*( Vector< DIMENSIONS, Scalar > const &other ) const
    {
        return this->dot( other );
    }

    Vector< DIMENSIONS, Scalar > &operator=( Vector< DIMENSIONS, Scalar > const &other )
    {
        for( position_t i = 0; i < _coordinates.size(); ++i )
        {
            _coordinates[i] = other._coordinates[i];
        }

        return *this;
    }

    Vector< DIMENSIONS, Scalar > &operator=( std::initializer_list< Scalar > values )
    {
        this->set( values );

        return *this;
    }

    private:
    std::array< typename std::enable_if< std::is_floating_point< Scalar >::value, Scalar >::type,
                DIMENSIONS >
        _coordinates;
};

#endif
