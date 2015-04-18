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
        Matrix(Matrix const &other);
        void reset_dimensions(position_t const &lines,position_t const &columns);
        MatrixDimensions dimensions(void) const;
        value_t determinant(void) const;
        void set(std::initializer_list<value_t> values,position_t const &lines,position_t const &columns);

        Matrix generate_minor(position_t const &line,position_t const &column) const;

        Matrix transposed(void) const;
        Matrix& transpose(void);
        Matrix cofactor_matrix(void);
        Matrix inverse(void);

        static Matrix identity_matrix(position_t const &lines,position_t const &columns);

        value_t * operator[](int const &line);
        value_t const * operator[](int const &line) const;

        Matrix operator*(Matrix const &other) const;
        Matrix operator*(value_t const &scalar) const;
        Matrix& operator*=(value_t const &scalar);

        Matrix& operator=(Matrix const &other);
    private:
        MatrixDimensions _dimensions;
        std::unique_ptr<value_t[]> _data;

        value_t inner_determinant(Matrix const &matrix) const;

        bool is_zero(value_t const &value) const;
};

#endif
