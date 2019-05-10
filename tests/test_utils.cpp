#include "test_utils.hpp"

void test_bool_value( bool value, bool expected_value, const std::string &function )
{
    BOOST_REQUIRE_MESSAGE( value == expected_value,
                           "\n   " << function << " returned an incorrect value.\n\t"
                                   << "Expected: " << ( expected_value ? "true" : "false" )
                                   << "\n\t"
                                   << "     Got: " << ( value ? "true" : "false" ) );
}

void test_string_value( const std::string &value,
                        const std::string &expected_value,
                        const std::string &function )
{
    BOOST_REQUIRE_MESSAGE( value.compare( expected_value ) == 0,
                           "\n   " << function << " returned an incorrect value.\n\t"
                                   << "Expected: " << expected_value << "\n\t"
                                   << "     Got: " << value );
}

void test_uint_value( unsigned int value, unsigned int expected_value, const std::string &function )
{
    BOOST_REQUIRE_MESSAGE( value == expected_value,
                           "\n   " << function << " returned an incorrect value.\n\t"
                                   << "Expected: " << expected_value << "\n\t"
                                   << "     Got: " << value );
}

// std::string get_tests_prefix(void)
// {
//     std::string prefix = bfs::canonical(bfs::absolute(".")).string();

//     prefix += "/tests/prefix";

//     return prefix;
// }
