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

        BOOST_CHECK_CLOSE( values.get_coordinate(i), expected.get_coordinate(i), 0.00001 );
    }
}

BOOST_AUTO_TEST_SUITE( VECTOR_CLASS_TEST_SUITE )

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

    BOOST_AUTO_TEST_CASE( multidimensional_vector_size_test )
    {
        Vector<37> vec;

        test_uint_value(   vec.dimensions(),
                            37,
                            "vec.dimensions()");
    }

    BOOST_AUTO_TEST_CASE( set_coordinate_test )
    {
        Vector<2> vec;

        vec.set_coordinate(0,1.0);

        BOOST_CHECK_CLOSE( vec.get_coordinate(0), 1.0, 0.00001 );

        vec.set_coordinate(0,5.5);

        BOOST_CHECK_CLOSE( vec.get_coordinate(0), 5.5, 0.00001 );

        vec.set_coordinate(1,3.3);

        BOOST_CHECK_CLOSE( vec.get_coordinate(1), 3.3, 0.00001 );

        vec.set_coordinate(1,9.2);

        BOOST_CHECK_CLOSE( vec.get_coordinate(1), 9.2, 0.00001 );
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

    BOOST_AUTO_TEST_CASE( empty_constructor_should_fill_with_zero_test )
    {
        Vector<3> vec1;

        const Vector<3> expected({0,0,0});

        test_vector_coordinates_equal(vec1,expected);
    }


    BOOST_AUTO_TEST_CASE( calculate_threedimensional_cross_product_test )
    {
        Vector<3> vec1({0,1,1});
        Vector<3> vec2({1,-1,3});

        Vector<3> product1 = vec1.cross(vec2);

        const Vector<3> expected1({4,1,-1});

        test_vector_coordinates_equal(product1,expected1);


        Vector<3> vec3({3,-3,1});
        Vector<3> vec4({4,9,2});

        Vector<3> product2 = vec3.cross(vec4);

        const Vector<3> expected2({-15,-2,39});

        test_vector_coordinates_equal(product2,expected2);
    }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */