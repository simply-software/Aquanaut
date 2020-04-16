#include <stdexcept>
#include "test_convert_from_string_double.h"
#include "../convert_from_string.h"


CPPUNIT_TEST_SUITE_REGISTRATION(test_convert_from_string_double);

test_convert_from_string_double::test_convert_from_string_double() {
    // Nothing to do
}

test_convert_from_string_double::~test_convert_from_string_double() {
    // Nothing to do
}

void test_convert_from_string_double::setUp() {
    // Nothing to do
}

void test_convert_from_string_double::tearDown() {
    // Nothing to do
}

void test_convert_from_string_double::positive_values() {
    double result;
    aqua::convert_from_string(result, "3.14");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14, result, 0.001);
}

void test_convert_from_string_double::handles_whitespace() {
    double result;
    aqua::convert_from_string(result, " 99.44 ");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(99.44, result, 0.001);
}

void test_convert_from_string_double::handles_negative_values() {
    double result;
    aqua::convert_from_string(result, "-1.732");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.732, result, 0.0001);
}

void test_convert_from_string_double::handles_decimal_point_with_no_fractional_part() {
    double result;
    aqua::convert_from_string(result, "42.");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(42.0, result, 0.0);
}

void test_convert_from_string_double::handles_integer_input() {
    double result;
    aqua::convert_from_string(result, "1414");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1414.0, result, 0.0);
}

void test_convert_from_string_double::precision() {
    double result;
    aqua::convert_from_string(result, "9.9999999999999999999");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(9.9999999999999999999, result, 0.0);
}

void test_convert_from_string_double::handles_scientific_notation() {
    double result;
    aqua::convert_from_string(result, "-3.14e-02");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0314, result, 0.00001);
}

void test_convert_from_string_double::throws_if_out_of_range() {
    double result;
    CPPUNIT_ASSERT_THROW(aqua::convert_from_string(result, "9e+4000"), std::range_error);
}

void test_convert_from_string_double::throws_if_invalid_input() {
    double result;
    CPPUNIT_ASSERT_THROW(aqua::convert_from_string(result, "garbage"), std::runtime_error);
}
