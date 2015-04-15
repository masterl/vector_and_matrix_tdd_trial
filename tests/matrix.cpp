#include <boost/test/unit_test.hpp>

#include "../src/matrix.hpp"

#include "test_utils.hpp"

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

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */
