#include "matrix.hpp"

#include <iostream>

using std::cout;
using std::endl;

Matrix::Matrix(void):
    _dimensions(std::make_pair(0,0))
{
}

void Matrix::reset_dimensions(position_t const &lines,position_t const &columns)
{
    _data.reset(new value_t[lines*columns]);

    _dimensions.first = lines;
    _dimensions.second = columns;
}

MatrixDimensions Matrix::dimensions(void)
{
    return _dimensions;
}

value_t* Matrix::operator[](int const &line)
{
    return &(_data.get()[line*_dimensions.second]);
}