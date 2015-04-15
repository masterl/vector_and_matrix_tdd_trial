#ifndef MATRIX_H
#define MATRIX_H

#include <utility>

typedef unsigned int position_t;
typedef std::pair<position_t,position_t> MatrixDimensions;

class Matrix
{
    public:
        Matrix(position_t const &lines,position_t const &columns);
        MatrixDimensions dimensions(void);
    private:
};

#endif
