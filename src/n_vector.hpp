#ifndef N_VECTOR_H
#define N_VECTOR_H

#include <array>
#include <cmath>
#include <initializer_list>

typedef unsigned int position_t;
typedef double scalar_t;

template <position_t DIMENSIONS,typename T = long int>
class Vector
{
    public:
        Vector<DIMENSIONS,T>(void)
        {
            _coordinates.fill(0);
        }

        Vector<DIMENSIONS,T>(Vector<DIMENSIONS,T> const &other)
        {
            for(position_t i = 0; i < other._coordinates.size(); ++i)
            {
                this->set_coordinate(i,other._coordinates[i]);
            }
        }

        Vector<DIMENSIONS,T>(std::initializer_list<T> values)
        {
            this->set(values);
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

        void set(std::initializer_list<T> values)
        {
            typename std::initializer_list<T>::iterator it = values.begin();

            for(position_t i = 0; (i < this->_coordinates.size()) && (it != values.end()); ++i)
            {
                this->_coordinates[i] = *it;
                ++it;
            }
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

        scalar_t cross(Vector<2,T> const &other) const
        {
            scalar_t product = 0.0;

            product = this->_coordinates[0] * other._coordinates[1];
            product -= this->_coordinates[1] * other._coordinates[0];

            return product;
        }

        // Vector<3,T> cross(Vector<3,T> const &other) const
        // {
        //     Vector<3,T> result;

        //     return result;
        // }

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
