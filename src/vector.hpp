#ifndef FIXED_VECTOR_H
#define FIXED_VECTOR_H

#include <array>

typedef unsigned int position_t;

template <position_t DIMENSIONS,typename Scalar>
class Vector
{
    public:
        inline position_t dimensions(void) const
        {
            return _coordinates.size();
        }

        Scalar& operator[](position_t const &&position)
        {
            return _coordinates.at(position);
        }

        Scalar const & operator[](position_t const &&position) const
        {
            return _coordinates.at(position);
        }
    private:
        std::array<Scalar,DIMENSIONS> _coordinates;
};

#endif
