#ifndef MATRIX_H
#define MATRIX_H

#include <utility>
#include <memory>
#include <algorithm>

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
        Matrix adjoint_matrix(void);
        Matrix generate_inverse(void);

        static Matrix identity_matrix(position_t const &lines,position_t const &columns);

        value_t * operator[](int const &line);
        value_t const * operator[](int const &line) const;

        Matrix operator*(Matrix const &other) const;
        Matrix operator/(Matrix const &other) const;
        Matrix operator+(Matrix const &other) const;
        Matrix operator-(Matrix const &other) const;


        Matrix operator*(value_t const &scalar) const;
        Matrix& operator*=(value_t const &scalar);
        Matrix operator/(value_t const &scalar) const;
        Matrix& operator/=(value_t const &scalar);
        Matrix operator+(value_t const &scalar) const;
        Matrix& operator+=(value_t const &scalar);
        Matrix operator-(value_t const &scalar) const;
        Matrix& operator-=(value_t const &scalar);

        Matrix& operator=(Matrix const &other);
    private:
        MatrixDimensions _dimensions;
        std::unique_ptr<value_t[]> _data;

        value_t inner_determinant(Matrix const &matrix) const;

        bool is_zero(value_t const &value) const;

        template <typename Function>
        void iterate_self(Function function)
        {
            Matrix &matrix = *this;
            MatrixDimensions dimensions;

            dimensions = matrix.dimensions();

            for(position_t i = 0; i < dimensions.first; ++i)
            {
                for(position_t j = 0; j < dimensions.second; ++j)
                {
                    function(matrix[i][j]);
                }
            }
        }

        template <typename Function>
        Matrix iterate_with_other(Matrix const &other,Function function) const
        {
            Matrix result;
            Matrix const &matrix = *this;
            MatrixDimensions dimensions;

            dimensions = matrix.dimensions();
            result.reset_dimensions(dimensions.first,dimensions.second);

            for(position_t i = 0; i < dimensions.first; ++i)
            {
                for(position_t j = 0; j < dimensions.second; ++j)
                {
                    result[i][j] = function(matrix[i][j],other[i][j]);
                }
            }

            return result;
        }
};

#endif
