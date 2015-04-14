#ifndef N_VECTOR_H
#define N_VECTOR_H

#include <array>
#include <cmath>

typedef unsigned int position_t;
typedef double scalar_t;

template <int DIMENSIONS,typename T = long int>
class Vector
{
    public:
        Vector<DIMENSIONS,T>(void)
        {
        }

        inline position_t dimensions(void) const
        {
            return this->_coordinates.size();
        }

        void set_coordinate(position_t const &pos,T const &value)
        {
            _coordinates.at(pos) = value;
        }

        T get_coordinate(position_t const &pos) const
        {
            return _coordinates.at(pos);
        }

        scalar_t distance_to(Vector<DIMENSIONS,T> const &other) const
        {
            scalar_t distance = 0.0;
            scalar_t diff;

            for(position_t i = 0; i < _coordinates.size(); ++i)
            {
                diff = this->_coordinates[i];
                diff -= other._coordinates[i];

                distance += diff * diff;
            }

            distance = sqrt(distance);

            return distance;
        }

        scalar_t dot(Vector<DIMENSIONS,T> const &other) const
        {
            scalar_t product = 0.0;

            for(position_t i = 0; i < _coordinates.size(); ++i)
            {
                product += this->_coordinates[i] * other._coordinates[i];
            }

            return product;
        }

        scalar_t operator*(Vector<DIMENSIONS,T> const &other) const
        {
            return this->dot(other);
        }

        Vector<DIMENSIONS,T> operator=(Vector<DIMENSIONS,T> const &other)
        {
            for(position_t i = 0; i < other._coordinates.size(); ++i)
            {
                this->set_coordinate(i,other._coordinates[i]);
            }

            return *this;
        }
    private:
        std::array<T,DIMENSIONS> _coordinates;
};

#endif
