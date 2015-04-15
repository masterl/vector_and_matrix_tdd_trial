#include "matrix.hpp"
#include <stdexcept>

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

value_t Matrix::determinant(void)
{
    value_t result = 0.0;

    if(_dimensions.first != _dimensions.second)
    {
        throw std::domain_error("This class can only compute determinant for square matrixes!");
    }

    switch(_dimensions.first)
    {
        case 1:
            result = (*this)[0][0];
            break;
        case 2:
            result  = (*this)[0][0] * (*this)[1][1];
            result -= (*this)[1][0] * (*this)[0][1];
            break;
        case 3:
            result  = (*this)[0][0] *
                        ( (*this)[1][1] * (*this)[2][2] -
                          (*this)[2][1] * (*this)[1][2]
                        );
            result -= (*this)[0][1] *
                        ( (*this)[1][0] * (*this)[2][2] -
                          (*this)[2][0] * (*this)[1][2]
                        );
            result += (*this)[0][2]
                        * ( (*this)[1][0] * (*this)[2][1] -
                            (*this)[2][0] * (*this)[1][1]
                          );
            break;
    }

    return result;
}







value_t* Matrix::operator[](int const &line)
{
    return &(_data.get()[line*_dimensions.second]);
}