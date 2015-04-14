#ifndef N_VECTOR_H
#define N_VECTOR_H

#include <array>

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
    private:
        std::array<T,DIMENSIONS> _coordinates;
};

#endif
