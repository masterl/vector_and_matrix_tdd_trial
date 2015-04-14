#include <boost/test/unit_test.hpp>

#include "../src/n_vector.hpp"

#include "test_utils.hpp"

template <position_t DIMENSIONS,typename T>
void test_vector_coordinates_equal(Vector<DIMENSIONS,T> const &values,Vector<DIMENSIONS,T> const &expected)
{
    std::string number;
    for(position_t i = 0; i < values.dimensions(); ++i)
    {
        number = std::to_string(i);
        test_uint_value(    values.get_coordinate(i),
                            expected.get_coordinate(i),
                            "values.get_coordinate(" + number + ") == "
                            "expected.get_coordinate(" + number + ")");
    }
}

BOOST_AUTO_TEST_SUITE( VECTOR_TEST_SUITE )

    BOOST_AUTO_TEST_CASE( unidimensional_vector_size_test )
    {
        Vector<1> vec;

        test_uint_value(   vec.dimensions(),
                            1,
                            "vec.dimensions()");
    }

    BOOST_AUTO_TEST_CASE( bidimensional_vector_size_test )
    {
        Vector<2> vec;

        test_uint_value(   vec.dimensions(),
                            2,
                            "vec.dimensions()");
    }

    BOOST_AUTO_TEST_CASE( set_coordinate_test )
    {
        Vector<2> vec;

        vec.set_coordinate(0,1);

        test_uint_value(   vec.get_coordinate(0),
                            1,
                            "vec.get_coordinate(0)");

        vec.set_coordinate(0,5);

        test_uint_value(   vec.get_coordinate(0),
                            5,
                            "vec.get_coordinate(0)");

        vec.set_coordinate(1,3);

        test_uint_value(   vec.get_coordinate(1),
                            3,
                            "vec.get_coordinate(1)");

        vec.set_coordinate(1,9);

        test_uint_value(   vec.get_coordinate(1),
                            9,
                            "vec.get_coordinate(1)");
    }

    BOOST_AUTO_TEST_CASE( get_coordinate_throws_out_of_range_exception_test )
    {
        Vector<2> vec;

        BOOST_REQUIRE_THROW(vec.get_coordinate(300), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE( set_coordinate_throws_out_of_range_exception_test )
    {
        Vector<2> vec;

        BOOST_REQUIRE_THROW(vec.set_coordinate(300,0), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE( calculate_vector_distance_test )
    {
        Vector<2> vec1;
        Vector<2> vec2;

        vec1.set_coordinate(0,0);
        vec1.set_coordinate(1,0);

        vec2.set_coordinate(0,3);
        vec2.set_coordinate(1,4);

        BOOST_CHECK_CLOSE( vec1.distance_to(vec2), 5.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( calculate_dot_product_test )
    {
        Vector<2> vec1;
        Vector<2> vec2;

        vec1.set_coordinate(0,0);
        vec1.set_coordinate(1,1);

        vec2.set_coordinate(0,3);
        vec2.set_coordinate(1,4);

        BOOST_CHECK_CLOSE( vec1.dot(vec2), 4.0, 0.00001 );

        vec2.set_coordinate(1,7);
        BOOST_CHECK_CLOSE( vec1.dot(vec2), 7.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( vector_multiplication_should_return_dot_product_test )
    {
        Vector<2> vec1;
        Vector<2> vec2;

        vec1.set_coordinate(0,0);
        vec1.set_coordinate(1,1);

        vec2.set_coordinate(0,4);
        vec2.set_coordinate(1,5);

        BOOST_CHECK_CLOSE( vec1 * vec2, 5.0, 0.00001 );

        vec2.set_coordinate(1,14);

        BOOST_CHECK_CLOSE( vec1 * vec2, 14.0, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( assignment_operator_test )
    {
        Vector<2> vec1;
        Vector<2> vec2;

        vec1.set_coordinate(0,0);
        vec1.set_coordinate(1,1);

        vec2.set_coordinate(0,23);
        vec2.set_coordinate(1,89);

        vec2 = vec1;

        test_vector_coordinates_equal(vec2,vec1);
    }

    BOOST_AUTO_TEST_CASE( calculate_bidimensional_cross_product_test )
    {
        Vector<2> vec1;
        Vector<2> vec2;

        vec1.set_coordinate(0,1);
        vec1.set_coordinate(1,1);

        vec2.set_coordinate(0,4);
        vec2.set_coordinate(1,5);

        scalar_t product = vec1.cross(vec2);

        BOOST_CHECK_CLOSE( product, 1, 0.00001 );

        vec2.set_coordinate(0,3);
        vec2.set_coordinate(1,17);

        product = vec1.cross(vec2);

        BOOST_CHECK_CLOSE( product, 14, 0.00001 );
    }

    BOOST_AUTO_TEST_CASE( initializer_list_set_test )
    {
        Vector<2> vec1;
        Vector<2> expected1;

        vec1.set({2,6});

        expected1.set_coordinate(0,2);
        expected1.set_coordinate(1,6);

        test_vector_coordinates_equal(vec1,expected1);

        Vector<3> vec2;
        Vector<3> expected2;

        vec2.set({11,35,27});

        expected2.set_coordinate(0,11);
        expected2.set_coordinate(1,35);
        expected2.set_coordinate(2,27);

        test_vector_coordinates_equal(vec2,expected2);
    }

    BOOST_AUTO_TEST_CASE( initializer_list_set_should_ignore_excess_values_test )
    {
        Vector<2> vec1;
        Vector<2> expected1;

        vec1.set({2,6,8,15,23,30});

        expected1.set_coordinate(0,2);
        expected1.set_coordinate(1,6);

        test_vector_coordinates_equal(vec1,expected1);

        Vector<3> vec2;
        Vector<3> expected2;

        vec2.set({11,35,27,21,33,675,1292,4545,1221,111,1});

        expected2.set_coordinate(0,11);
        expected2.set_coordinate(1,35);
        expected2.set_coordinate(2,27);

        test_vector_coordinates_equal(vec2,expected2);
    }

    BOOST_AUTO_TEST_CASE( initializer_list_constructor_test )
    {
        Vector<2> vec1({2,6});
        Vector<2> expected1;

        expected1.set_coordinate(0,2);
        expected1.set_coordinate(1,6);

        test_vector_coordinates_equal(vec1,expected1);

        Vector<3> vec2({11,35,27});
        Vector<3> expected2;

        expected2.set_coordinate(0,11);
        expected2.set_coordinate(1,35);
        expected2.set_coordinate(2,27);

        test_vector_coordinates_equal(vec2,expected2);
    }

    // BOOST_AUTO_TEST_CASE( calculate_threedimensional_cross_product_test )
    // {
    //     Vector<3> vec1;
    //     Vector<3> vec2;

    //     vec1.set_coordinate(0,1);
    //     vec1.set_coordinate(1,1);
    //     vec1.set_coordinate(2,1);

    //     vec2.set_coordinate(0,4);
    //     vec2.set_coordinate(1,5);
    //     vec2.set_coordinate(1,6);

    //     Vector<3> product = vec1.cross(vec2);

    //     BOOST_TEST_MESSAGE( "lixo" );
    // }

    // BOOST_AUTO_TEST_CASE( forth_or_greater_dimension_cross_product_throws_out_of_range_exception_test )
    // {
    //     Vector<4> vec1;
    //     Vector<4> vec2;

    //     BOOST_REQUIRE_THROW(vec1.cross(vec2), std::length_error);
    // }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */