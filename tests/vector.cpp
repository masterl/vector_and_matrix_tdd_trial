#include <boost/test/unit_test.hpp>

#include "../src/n_vector.hpp"

BOOST_AUTO_TEST_SUITE( VECTOR_TEST_SUITE )

    BOOST_AUTO_TEST_CASE( unidimensional_vector_size_test )
    {
        Vector<1> vec;

        BOOST_REQUIRE( vec.dimensions() == 1);
    }

    BOOST_AUTO_TEST_CASE( bidimensional_vector_size_test )
    {
        Vector<2> vec;

        BOOST_REQUIRE( vec.dimensions() == 2);
    }

    // BOOST_AUTO_TEST_CASE( set_coordinate_0_to_1_test )
    // {
    //     Vector<2> vec;

    //     vec.set_coordinate(0,1);

    //     BOOST_REQUIRE( vec.get_coordinate(0) == 1 );
    // }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */