#ifndef MATRIX_H
#define MATRIX_H

#include <utility>
#include <memory>

typedef unsigned int position_t;
typedef double value_t;
typedef std::pair<position_t,position_t> MatrixDimensions;

class Matrix
{
    public:
        Matrix(void);
        void reset_dimensions(position_t const &lines,position_t const &columns);
        MatrixDimensions dimensions(void);
        value_t determinant(void);

        value_t* operator[](int const &line);
    private:
        MatrixDimensions _dimensions;
        std::unique_ptr<value_t[]> _data;


};

#endif
