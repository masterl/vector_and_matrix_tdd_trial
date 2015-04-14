#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <boost/test/unit_test.hpp>
// #include <boost/filesystem.hpp>
#include <string>

// namespace bfs = boost::filesystem;

void test_bool_value(bool value,bool expected_value,const std::string &function);
void test_string_value(const std::string &value,const std::string &expected_value,const std::string &function);
void test_uint_value(unsigned int value,unsigned int expected_value,const std::string &function);

// std::string get_tests_prefix(void);

#endif
