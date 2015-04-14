#ifndef N_VECTOR_H
#define N_VECTOR_H

#include <array>
#include <cmath>

typedef unsigned int position_t;

template <int DIMENSIONS,typename T = int>
class Vector
{
    public:
        Vector(void)
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
        T get_coordinate(position_t const &pos)
        {
            return _coordinates.at(pos);
        }
        double distance_to(Vector<DIMENSIONS,T> const &other)
        {
            double distance = 0.0;
            double diff;

            for(position_t i = 0; i < _coordinates.size(); ++i)
            {
                diff = this->_coordinates[i];
                diff -= other._coordinates[i];

                distance += diff * diff;
            }

            distance = sqrt(distance);

            return distance;
        }
    private:
        std::array<T,DIMENSIONS> _coordinates;
};

#endif
