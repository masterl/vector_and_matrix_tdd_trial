#include <boost/test/unit_test.hpp>

#include "../src/vector.hpp"

#include "test_utils.hpp"

template < position_t DIMENSIONS, typename T >
void test_vector_coordinates_equal( Vector< DIMENSIONS, T > const &values,
                                    Vector< DIMENSIONS, T > const &expected )
{
    for( position_t i = 0; i < values.dimensions(); ++i )
    {
        BOOST_CHECK_CLOSE( values[i], expected[i], 0.00001 );
    }
}

BOOST_AUTO_TEST_SUITE( VECTOR_CLASS_TEST_SUITE )

BOOST_AUTO_TEST_CASE( unidimensional_vector_size_test )
{
    Vector< 1, double > vec;

    test_uint_value( vec.dimensions(), 1, "vec.dimensions()" );
}

BOOST_AUTO_TEST_CASE( bidimensional_vector_size_test )
{
    Vector< 2, double > vec;

    test_uint_value( vec.dimensions(), 2, "vec.dimensions()" );
}

BOOST_AUTO_TEST_CASE( set_coordinate_test )
{
    Vector< 2, double > vec;

    vec[0] = 1.0;

    BOOST_CHECK_CLOSE( vec[0], 1.0, 0.00001 );

    vec[0] = 5.5;

    BOOST_CHECK_CLOSE( vec[0], 5.5, 0.00001 );

    vec[1] = 7.3;

    BOOST_CHECK_CLOSE( vec[1], 7.3, 0.00001 );
}

BOOST_AUTO_TEST_CASE( getting_coordinate_throws_out_of_range_exception_test )
{
    Vector< 2, double > vec;

    BOOST_REQUIRE_THROW( vec[300], std::out_of_range );
}

BOOST_AUTO_TEST_CASE( calculate_vector_distance_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > vec2;

    vec1[0] = 0.0;
    vec1[1] = 0.0;

    vec2[0] = 3.0;
    vec2[1] = 4.0;

    BOOST_CHECK_CLOSE( vec1.distance_to( vec2 ), 5.0, 0.00001 );
}

BOOST_AUTO_TEST_CASE( calculate_dot_product_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > vec2;

    vec1[0] = 0.0;
    vec1[1] = 1.0;

    vec2[0] = 3.0;
    vec2[1] = 4.0;

    BOOST_CHECK_CLOSE( vec1.dot( vec2 ), 4.0, 0.00001 );

    vec2[1] = 7.0;

    BOOST_CHECK_CLOSE( vec1.dot( vec2 ), 7.0, 0.00001 );
}

BOOST_AUTO_TEST_CASE( vector_multiplication_should_return_dot_product_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > vec2;

    vec1[0] = 0.0;
    vec1[1] = 1.0;

    vec2[0] = 4.0;
    vec2[1] = 5.0;

    BOOST_CHECK_CLOSE( vec1 * vec2, 5.0, 0.00001 );

    vec2[1] = 14.0;

    BOOST_CHECK_CLOSE( vec1 * vec2, 14.0, 0.00001 );
}

BOOST_AUTO_TEST_CASE( assignment_operator_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > vec2;

    vec1[0] = 0.0;
    vec1[1] = 1.0;

    vec2[0] = 23.0;
    vec2[1] = 89.0;

    vec2 = vec1;

    test_vector_coordinates_equal( vec2, vec1 );
}

BOOST_AUTO_TEST_CASE( calculate_bidimensional_cross_product_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > vec2;

    vec1[0] = 1.0;
    vec1[1] = 1.0;

    vec2[0] = 4.0;
    vec2[1] = 5.0;

    double product = vec1.cross( vec2 );

    BOOST_CHECK_CLOSE( product, 1.0, 0.00001 );

    vec2[0] = 3.0;
    vec2[1] = 17.0;

    product = vec1.cross( vec2 );

    BOOST_CHECK_CLOSE( product, 14.0, 0.00001 );
}

BOOST_AUTO_TEST_CASE( initializer_list_set_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > expected1;

    vec1.set( {2.0, 6.0} );

    expected1[0] = 2.0;
    expected1[1] = 6.0;

    test_vector_coordinates_equal( vec1, expected1 );

    Vector< 3, double > vec2;
    Vector< 3, double > expected2;

    vec2.set( {11.0, 35.0, 27.0} );

    expected2[0] = 11.0;
    expected2[1] = 35.0;
    expected2[2] = 27.0;

    test_vector_coordinates_equal( vec2, expected2 );
}

BOOST_AUTO_TEST_CASE( initializer_list_assign_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > expected1;

    vec1 = {3.0, 4.5};

    expected1[0] = 3.0;
    expected1[1] = 4.5;

    test_vector_coordinates_equal( vec1, expected1 );

    Vector< 3, double > vec2;
    Vector< 3, double > expected2;

    vec2 = {15.2, 47.5, 37.8};

    expected2[0] = 15.2;
    expected2[1] = 47.5;
    expected2[2] = 37.8;

    test_vector_coordinates_equal( vec2, expected2 );
}

BOOST_AUTO_TEST_CASE( initializer_list_set_should_ignore_excess_values_test )
{
    Vector< 2, double > vec1;
    Vector< 2, double > expected1;

    vec1.set( {2.0, 6.0, 8.0, 15.0, 23.0, 30.0} );

    expected1[0] = 2.0;
    expected1[1] = 6.0;

    test_vector_coordinates_equal( vec1, expected1 );

    Vector< 3, double > vec2;
    Vector< 3, double > expected2;

    vec2.set( {11, 35, 27, 21, 33, 675, 1292, 4545, 1221, 111, 1} );

    expected2[0] = 11.0;
    expected2[1] = 35.0;
    expected2[2] = 27.0;

    test_vector_coordinates_equal( vec2, expected2 );
}

BOOST_AUTO_TEST_CASE( initializer_list_constructor_test )
{
    Vector< 2, double > vec1( {2.0, 6.0} );
    Vector< 2, double > expected1;

    expected1[0] = 2.0;
    expected1[1] = 6.0;

    test_vector_coordinates_equal( vec1, expected1 );

    Vector< 3, double > vec2( {11.0, 35.0, 27.0} );
    Vector< 3, double > expected2;

    expected2[0] = 11.0;
    expected2[1] = 35.0;
    expected2[2] = 27.0;

    test_vector_coordinates_equal( vec2, expected2 );
}

BOOST_AUTO_TEST_CASE( empty_constructor_should_fill_with_zero_test )
{
    Vector< 3, double > vec1;

    const Vector< 3, double > expected( {0, 0, 0} );

    test_vector_coordinates_equal( vec1, expected );
}

BOOST_AUTO_TEST_CASE( calculate_threedimensional_cross_product_test )
{
    Vector< 3, double > vec1( {0, 1, 1} );
    Vector< 3, double > vec2( {1, -1, 3} );

    Vector< 3, double > product1 = vec1.cross( vec2 );

    const Vector< 3, double > expected1( {4, 1, -1} );

    test_vector_coordinates_equal( product1, expected1 );

    Vector< 3, double > vec3( {3, -3, 1} );
    Vector< 3, double > vec4( {4, 9, 2} );

    Vector< 3, double > product2 = vec3.cross( vec4 );

    const Vector< 3, double > expected2( {-15, -2, 39} );

    test_vector_coordinates_equal( product2, expected2 );
}

BOOST_AUTO_TEST_SUITE_END()
/* src/vector.hpp test suite end */
