#include <boost/test/unit_test.hpp>

#include "../src/matrix.hpp"

#include "test_utils.hpp"

void test_matrix_equal(Matrix const &values,Matrix const &expected)
{
    MatrixDimensions values_dimensions;
    MatrixDimensions expected_dimensions;

    values_dimensions = values.dimensions();
    expected_dimensions = expected.dimensions();

    if( (values_dimensions.first != expected_dimensions.first) ||
        (values_dimensions.second != expected_dimensions.second) )
    {
        std::string msg;

        msg = "\nCalculated matrix: ";
        msg += std::to_string(values_dimensions.first) + "x" + std::to_string(values_dimensions.second);
        msg += "\n  Expected matrix: ";
        msg += std::to_string(expected_dimensions.first) + "x" + std::to_string(expected_dimensions.second);
        throw std::range_error("Matrix dimensions differ!" + msg + "\n");
    }

    for(unsigned int i = 0; i < values_dimensions.first; ++i)
    {
        for(unsigned int j = 0; j < values_dimensions.first; ++j)
        {
            BOOST_CHECK_CLOSE( values[i][j], expected[i][j], 0.00001 );
        }
    }
}

BOOST_AUTO_TEST_SUITE( MATRIX_CLASS_TEST_SUITE )

    BOOST_AUTO_TEST_CASE( matrix_size_test )
    {
        Matrix matrix1;

        matrix1.reset_dimensions(1,1);

        MatrixDimensions dimensions1 = matrix1.dimensions();

        test_uint_value(   dimensions1.first,
                            1,
                            "dimensions1.first");

        test_uint_value(   dimensions1.second,
                            1,
                            "dimensions1.second");

        Matrix matrix2;

        matrix2.reset_dimensions(3,5);

        MatrixDimensions dimensions2 = matrix2.dimensions();

        test_uint_value(   dimensions2.first,
                            3,
                            "dimensions2.first");

        test_uint_value(   dimensions2.second,
                            5,
                            "dimensions2.second");
    }

    BOOST_AUTO_TEST_CASE( assign_value_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(2,2);

        matrix[0][0] = 2.0;
        matrix[0][1] = 4.5;
        matrix[1][0] = 3.1;
        matrix[1][1] = 7.024;

        BOOST_CHECK_CLOSE( matrix[0][0],   2.0, 0.00001 );
        BOOST_CHECK_CLOSE( matrix[0][1],   4.5, 0.00001 );
        BOOST_CHECK_CLOSE( matrix[1][0],   3.1, 0.00001 );
        BOOST_CHECK_CLOSE( matrix[1][1], 7.024, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( calculate_1x1_determinant_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(1,1);

        matrix[0][0] = 3.3;

        BOOST_CHECK_CLOSE( matrix.determinant(),   3.3, 0.00001 );

        matrix[0][0] = 7.1;

        BOOST_CHECK_CLOSE( matrix.determinant(),   7.1, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( calculate_2x2_determinant_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(2,2);

        matrix[0][0] = 3.0;
        matrix[0][1] = 8.0;
        matrix[1][0] = 4.0;
        matrix[1][1] = 6.0;


        BOOST_CHECK_CLOSE( matrix.determinant(),   -14, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( calculate_3x3_determinant_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(3,3);

        matrix[0][0] =  6.0;
        matrix[0][1] =  1.0;
        matrix[0][2] =  1.0;
        matrix[1][0] =  4.0;
        matrix[1][1] = -2.0;
        matrix[1][2] =  5.0;
        matrix[2][0] =  2.0;
        matrix[2][1] =  8.0;
        matrix[2][2] =  7.0;


        BOOST_CHECK_CLOSE( matrix.determinant(),   -306.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_nonsquare_determinant_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(1,3);

        matrix[0][0] =  3.0;
        matrix[0][1] =  1.0;
        matrix[0][2] =  6.0;


        BOOST_REQUIRE_THROW( matrix.determinant(), std::domain_error);
    }

    BOOST_AUTO_TEST_CASE( calculate_1x1_matrix_multiplication_test )
    {
        Matrix matrix1;
        Matrix matrix2;
        Matrix expected;

        matrix1.reset_dimensions(1,1);
        matrix2.reset_dimensions(1,1);
        expected.reset_dimensions(1,1);

        matrix1[0][0]  =  3.0;
        matrix2[0][0]  =  7.0;
        expected[0][0] = 21.0;

        Matrix result = matrix1 * matrix2;

        test_matrix_equal(result, expected);
    }

    BOOST_AUTO_TEST_CASE( calculate_2x2_matrix_multiplication_test )
    {
        Matrix matrix1;
        Matrix matrix2;
        Matrix expected;

        matrix1.reset_dimensions(2,2);
        matrix2.reset_dimensions(2,2);
        expected.reset_dimensions(2,2);

        matrix1[0][0]  =  3.0;
        matrix1[0][1]  =  1.0;
        matrix1[1][0]  =  2.0;
        matrix1[1][1]  =  2.0;

        matrix2[0][0]  =  1.0;
        matrix2[0][1]  =  1.0;
        matrix2[1][0]  =  4.0;
        matrix2[1][1]  =  4.0;

        expected[0][0]  =  7.0;
        expected[0][1]  =  7.0;
        expected[1][0]  = 10.0;
        expected[1][1]  = 10.0;

        Matrix result = matrix1 * matrix2;

        test_matrix_equal(result, expected);
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_invalid_multiplication_test )
    {
        Matrix matrix1;
        Matrix matrix2;

        matrix1.reset_dimensions(2,1);
        matrix2.reset_dimensions(3,4);

        BOOST_REQUIRE_THROW( matrix1 * matrix2, std::domain_error );
    }

    BOOST_AUTO_TEST_CASE( set_matrix_with_initializer_list_test )
    {
        Matrix expected;
        Matrix values;

        values.set( {   3.0, 2.0, 0.0,
                        4.0, 0.0, 1.0,
                        3.0, 0.0, 2.0
                    },
                    3, 3 );

        expected.reset_dimensions(3,3);

        expected[0][0] =  3.0;
        expected[0][1] =  2.0;
        expected[0][2] =  0.0;
        expected[1][0] =  4.0;
        expected[1][1] =  0.0;
        expected[1][2] =  1.0;
        expected[2][0] =  3.0;
        expected[2][1] =  0.0;
        expected[2][2] =  2.0;

        test_matrix_equal(values,expected);
    }

    BOOST_AUTO_TEST_CASE( generate_minor_from_4x4_test )
    {
        Matrix matrix;
        Matrix expected;
        Matrix minor;

        matrix.set( {   3.0, 2.0, 0.0, 1.0,
                        4.0, 0.0, 1.0, 2.0,
                        3.0, 0.0, 2.0, 1.0,
                        9.0, 2.0, 3.0, 1.0
                    },
                    4, 4 );

        expected.set( { 3.0, 0.0, 1.0,
                        3.0, 2.0, 1.0,
                        9.0, 3.0, 1.0
                    },
                    3, 3 );

        minor = matrix.generate_minor(1,1);

        test_matrix_equal(minor,expected);
    }

    BOOST_AUTO_TEST_CASE( calculate_4x4_determinant_test )
    {
        Matrix matrix;

        matrix.set( {   3.0, 2.0, 0.0, 1.0,
                        4.0, 0.0, 1.0, 2.0,
                        3.0, 0.0, 2.0, 1.0,
                        9.0, 2.0, 3.0, 1.0
                    },
                    4, 4 );

        BOOST_CHECK_CLOSE( matrix.determinant(),   24.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( calculate_5x5_determinant_test )
    {
        Matrix matrix;

        matrix.set( {   5.0, 2.0, 0.0, 0.0, -2.0,
                        0.0, 1.0, 4.0, 3.0,  2.0,
                        0.0, 0.0, 2.0, 6.0,  3.0,
                        0.0, 0.0, 3.0, 4.0,  1.0,
                        0.0, 0.0, 0.0, 0.0,  2.0
                    },
                    5, 5 );

        BOOST_CHECK_CLOSE( matrix.determinant(),   -100.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( assign_matrix_test )
    {
        Matrix matrix;
        Matrix result;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        result = matrix;

        test_matrix_equal(result,expected);
    }

    BOOST_AUTO_TEST_CASE( multiply_by_scalar_test )
    {
        Matrix matrix;
        Matrix result;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 10.0, 4.0,
                         0.0, 2.0
                    },
                    2, 2 );

        result = matrix * 2;

        test_matrix_equal(result,expected);
    }

    BOOST_AUTO_TEST_CASE( multiply_and_assign_by_scalar_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 15.0, 6.0,
                         0.0, 3.0
                    },
                    2, 2 );

        matrix *= 3;

        test_matrix_equal(matrix,expected);
    }

    BOOST_AUTO_TEST_CASE( get_an_identity_matrix_test )
    {
        Matrix matrix = Matrix::identity_matrix(2,2);
        Matrix expected;

        expected.set( { 1.0, 0.0,
                        0.0, 1.0
                    },
                    2, 2 );

        test_matrix_equal(matrix,expected);

        matrix = Matrix::identity_matrix(3,3);

        expected.set( { 1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 0.0, 1.0
                    },
                    3, 3 );

        test_matrix_equal(matrix,expected);
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_invalid_dimensions_inverse_test )
    {
        Matrix matrix;

        matrix.reset_dimensions(1,4);

        BOOST_REQUIRE_THROW( matrix.generate_inverse(), std::domain_error );
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_zero_determinant_inverse_test )
    {
        Matrix matrix;

        matrix.set( {   0.0, 0.0,
                        0.0, 0.0
                    },
                    2, 2);

        BOOST_REQUIRE_THROW( matrix.generate_inverse(), std::domain_error );
    }

    BOOST_AUTO_TEST_CASE( get_transposed_matrix_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   1.0, 2.0, 3.0,
                        4.0, 5.0, 6.0,
                        7.0, 8.0, 9.0
                    },
                    3, 3);

        expected.set( { 1.0, 4.0, 7.0,
                        2.0, 5.0, 8.0,
                        3.0, 6.0, 9.0
                    },
                    3, 3);

        test_matrix_equal(matrix.transposed(), expected);

        matrix.set( {   1.0, 2.0, 3.0,
                        4.0, 5.0, 6.0
                    },
                    2, 3);

        expected.set( { 1.0, 4.0,
                        2.0, 5.0,
                        3.0, 6.0
                    },
                    3, 2);

        test_matrix_equal(matrix.transposed(), expected);
    }

    BOOST_AUTO_TEST_CASE( transpose_matrix_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   1.0, 2.0, 3.0,
                        4.0, 5.0, 6.0,
                        7.0, 8.0, 9.0
                    },
                    3, 3);

        expected.set( { 1.0, 4.0, 7.0,
                        2.0, 5.0, 8.0,
                        3.0, 6.0, 9.0
                    },
                    3, 3);

        matrix.transpose();

        test_matrix_equal(matrix, expected);
    }

    BOOST_AUTO_TEST_CASE( get_cofactor_matrix_test )
    {
        Matrix matrix;
        Matrix cofactor_matrix;
        Matrix expected;

        matrix.set( {   1.0, 2.0, 3.0,
                        0.0, 4.0, 5.0,
                        1.0, 0.0, 6.0
                    },
                    3, 3);

        expected.set( {  24.0,  5.0, -4.0,
                        -12.0,  3.0,  2.0,
                         -2.0, -5.0,  4.0
                    },
                    3, 3);

        cofactor_matrix = matrix.cofactor_matrix();

        test_matrix_equal(cofactor_matrix, expected);
    }

    BOOST_AUTO_TEST_CASE( get_adjoint_matrix_test )
    {
        Matrix matrix;
        Matrix adjoint_matrix;
        Matrix expected;

        matrix.set( {   1.0, 2.0, 3.0,
                        0.0, 4.0, 5.0,
                        1.0, 0.0, 6.0
                    },
                    3, 3);

        expected.set( { 24.0, -12.0, -2.0,
                         5.0,   3.0, -5.0,
                        -4.0,   2.0,  4.0
                    },
                    3, 3);

        adjoint_matrix = matrix.adjoint_matrix();

        test_matrix_equal(adjoint_matrix, expected);
    }

    BOOST_AUTO_TEST_CASE( divide_by_scalar_test )
    {
        Matrix matrix;
        Matrix result;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 2.5, 1.0,
                        0.0, 0.5
                    },
                    2, 2 );

        result = matrix / 2;

        test_matrix_equal(result,expected);
    }

    BOOST_AUTO_TEST_CASE( divide_and_assign_by_scalar_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 1.25, 0.5,
                         0.0, 0.25
                    },
                    2, 2 );

        matrix /= 4;

        test_matrix_equal(matrix,expected);
    }

    BOOST_AUTO_TEST_CASE( get_inverse_matrix_test )
    {
        Matrix matrix;
        Matrix inverse_matrix;
        Matrix expected;

        matrix.set( {   3.0, 0.0,  2.0,
                        2.0, 0.0, -2.0,
                        0.0, 1.0,  1.0
                    },
                    3, 3);

        expected.set( {  0.2,  0.2, 0.0,
                        -0.2,  0.3, 1.0,
                         0.2, -0.3, 0.0
                    },
                    3, 3);

        inverse_matrix = matrix.generate_inverse();

        test_matrix_equal(inverse_matrix, expected);
    }

    BOOST_AUTO_TEST_CASE( sum_two_matrixes_test )
    {
        Matrix matrix1;
        Matrix matrix2;
        Matrix result;
        Matrix expected;

        matrix1.set( {  3.0, 0.0,  2.0,
                        2.0, 0.0, -2.0,
                        0.0, 1.0,  1.0
                    },
                    3, 3);

        matrix2.set( {  0.0, 3.0, -1.0,
                        2.0, 1.0, -2.0,
                        5.0, 2.0,  1.0
                    },
                    3, 3);

        expected.set( {  3.0, 3.0,  1.0,
                         4.0, 1.0, -4.0,
                         5.0, 3.0,  2.0
                    },
                    3, 3);

        result = matrix1 + matrix2;

        test_matrix_equal(result, expected);
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_invalid_sum_test )
    {
        Matrix matrix1;
        Matrix matrix2;

        matrix1.reset_dimensions(2,1);
        matrix2.reset_dimensions(3,4);

        BOOST_REQUIRE_THROW( matrix1 + matrix2, std::domain_error );
    }

    BOOST_AUTO_TEST_CASE( subtract_two_matrixes_test )
    {
        Matrix matrix1;
        Matrix matrix2;
        Matrix result;
        Matrix expected;

        matrix1.set( {  3.0, 0.0,  2.0,
                        2.0, 0.0, -2.0,
                        0.0, 1.0,  1.0
                    },
                    3, 3);

        matrix2.set( {  0.0, 3.0, -1.0,
                        2.0, 1.0, -2.0,
                        5.0, 2.0,  1.0
                    },
                    3, 3);

        expected.set( {  3.0, -3.0, 3.0,
                         0.0, -1.0, 0.0,
                        -5.0, -1.0, 0.0
                    },
                    3, 3);

        result = matrix1 - matrix2;

        test_matrix_equal(result, expected);
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_invalid_subtract_test )
    {
        Matrix matrix1;
        Matrix matrix2;

        matrix1.reset_dimensions(2,1);
        matrix2.reset_dimensions(3,4);

        BOOST_REQUIRE_THROW( matrix1 - matrix2, std::domain_error );
    }

    BOOST_AUTO_TEST_CASE( sum_scalar_test )
    {
        Matrix matrix;
        Matrix result;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 7.0, 4.0,
                        2.0, 3.0
                    },
                    2, 2 );

        result = matrix + 2;

        test_matrix_equal(result,expected);
    }

    BOOST_AUTO_TEST_CASE( sum_and_assign_scalar_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( { 8.0, 5.0,
                        3.0, 4.0
                    },
                    2, 2 );

        matrix += 3;

        test_matrix_equal(matrix,expected);
    }

    BOOST_AUTO_TEST_CASE( subtract_scalar_test )
    {
        Matrix matrix;
        Matrix result;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( {  2.0, -1.0,
                        -3.0, -2.0
                    },
                    2, 2 );

        result = matrix - 3;

        test_matrix_equal(result,expected);
    }

    BOOST_AUTO_TEST_CASE( subtract_and_assign_scalar_test )
    {
        Matrix matrix;
        Matrix expected;

        matrix.set( {   5.0, 2.0,
                        0.0, 1.0
                    },
                    2, 2 );

        expected.set( {  0.0, -3.0,
                        -5.0, -4.0
                    },
                    2, 2 );

        matrix -= 5;

        test_matrix_equal(matrix,expected);
    }

    BOOST_AUTO_TEST_CASE( calculate_matrix_element_division_test )
    {
        Matrix matrix1;
        Matrix matrix2;
        Matrix expected;

        matrix1.set( {  3.0, 1.0,
                        2.0, 2.0
                    },
                    2, 2 );

        matrix2.set( {  3.0, 5.0,
                        4.0, 8.0
                    },
                    2, 2 );

        expected.set( { 1.0, 0.2,
                        0.5, 0.25
                    },
                    2, 2 );

        Matrix result = matrix1 / matrix2;

        test_matrix_equal(result, expected);
    }

    BOOST_AUTO_TEST_CASE( throw_domain_error_for_invalid_element_division_test )
    {
        Matrix matrix1;
        Matrix matrix2;

        matrix1.reset_dimensions(2,1);
        matrix2.reset_dimensions(3,4);

        BOOST_REQUIRE_THROW( matrix1 / matrix2, std::domain_error );
    }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */
