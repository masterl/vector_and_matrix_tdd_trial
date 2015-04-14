#ifndef N_VECTOR_H
#define N_VECTOR_H

#include <array>

template <int DIMENSIONS,typename T = int>
class Vector
{
    public:
        Vector(void)
        {
        }
        inline unsigned int dimensions(void)
        {
            return this->_coordinates.size();
        }
    private:
        std::array<T,DIMENSIONS> _coordinates;
};

#endif
