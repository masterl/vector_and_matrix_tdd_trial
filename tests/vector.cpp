#include <boost/test/unit_test.hpp>

#include "../src/n_vector.hpp"

#include "test_utils.hpp"

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

        test_uint_value(    vec1.get_coordinate(0),
                            vec2.get_coordinate(0),
                            "vec2.get_coordinate(0) = vec1.get_coordinate(0)");
        test_uint_value(    vec1.get_coordinate(1),
                            vec2.get_coordinate(1),
                            "vec2.get_coordinate(1) = vec1.get_coordinate(1)");
    }

    // BOOST_AUTO_TEST_CASE( calculate_cross_product_test )
    // {
    //     Vector<2> vec1;
    //     Vector<2> vec2;

    //     vec1.set_coordinate(0,0);
    //     vec1.set_coordinate(1,1);

    //     vec2.set_coordinate(0,4);
    //     vec2.set_coordinate(1,5);

    //     BOOST_CHECK_CLOSE( vec1 * vec2, 5.0, 0.00001 );

    //     vec2.set_coordinate(1,14);

    //     BOOST_CHECK_CLOSE( vec1 * vec2, 14.0, 0.00001 );
    // }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */