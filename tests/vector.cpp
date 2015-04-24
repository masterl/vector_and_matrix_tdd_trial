#include <boost/test/unit_test.hpp>

#include "../src/vector.hpp"

#include "test_utils.hpp"

BOOST_AUTO_TEST_SUITE( VECTOR_CLASS_TEST_SUITE )

    BOOST_AUTO_TEST_CASE( unidimensional_vector_size_test )
    {
        Vector<1,double> vec;

        test_uint_value(   vec.dimensions(),
                            1,
                            "vec.dimensions()");
    }

    BOOST_AUTO_TEST_CASE( bidimensional_vector_size_test )
    {
        Vector<2,double> vec;

        test_uint_value(   vec.dimensions(),
                            2,
                            "vec.dimensions()");
    }

    BOOST_AUTO_TEST_CASE( set_coordinate_test )
    {
        Vector<2,double> vec;

        vec[0] = 1.0;

        BOOST_CHECK_CLOSE( vec[0], 1.0, 0.00001 );

        vec[0] = 5.5;

        BOOST_CHECK_CLOSE( vec[0], 5.5, 0.00001 );

        vec[1] = 7.3;

        BOOST_CHECK_CLOSE( vec[1], 7.3, 0.00001 );
    }

BOOST_AUTO_TEST_SUITE_END()
/* src/vector.hpp test suite end */