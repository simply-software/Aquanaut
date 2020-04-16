#pragma once

#include <cppunit/extensions/HelperMacros.h>

class test_convert_from_string_double : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_convert_from_string_double);

    CPPUNIT_TEST(positive_values);
    CPPUNIT_TEST(handles_whitespace);
    CPPUNIT_TEST(handles_negative_values);
    CPPUNIT_TEST(handles_decimal_point_with_no_fractional_part);
    CPPUNIT_TEST(handles_integer_input);
    CPPUNIT_TEST(precision);
    CPPUNIT_TEST(handles_scientific_notation);
    CPPUNIT_TEST(throws_if_out_of_range);
    CPPUNIT_TEST(throws_if_invalid_input);

    CPPUNIT_TEST_SUITE_END();

public:
    test_convert_from_string_double();
    virtual ~test_convert_from_string_double();
    void setUp();
    void tearDown();

private:
    void positive_values();
    void handles_whitespace();
    void handles_negative_values();
    void handles_decimal_point_with_no_fractional_part();
    void handles_integer_input();
    void precision();
    void handles_scientific_notation();
    void throws_if_out_of_range();
    void throws_if_invalid_input();

};
