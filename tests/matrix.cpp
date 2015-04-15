#include <boost/test/unit_test.hpp>

#include "../src/matrix.hpp"

#include "test_utils.hpp"

BOOST_AUTO_TEST_SUITE( MATRIX_CLASS_TEST_SUITE )

    BOOST_AUTO_TEST_CASE( matrix_1x1_size_test )
    {
        Matrix matrix(1,1);

        MatrixDimensions dimensions = matrix.dimensions();

        test_uint_value(   dimensions.first,
                            1,
                            "dimensions.first");

        test_uint_value(   dimensions.second,
                            1,
                            "dimensions.first");
    }

BOOST_AUTO_TEST_SUITE_END()
/* src/Vector test suite end */
