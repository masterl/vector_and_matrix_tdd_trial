#include "matrix.hpp"

Matrix::Matrix(position_t const &lines,position_t const &columns)
{
}

MatrixDimensions Matrix::dimensions(void)
{
    return std::make_pair(1,1);
}