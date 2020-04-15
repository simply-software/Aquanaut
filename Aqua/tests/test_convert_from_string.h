/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   test_convert_from_string.h
 * Author: Jay
 *
 * Created on Apr 15, 2020, 8:44:26 AM
 */

#ifndef TEST_CONVERT_FROM_STRING_H
#define TEST_CONVERT_FROM_STRING_H

#include <cppunit/extensions/HelperMacros.h>

class test_convert_from_string : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_convert_from_string);

    CPPUNIT_TEST(testConvert_from_string);

    CPPUNIT_TEST_SUITE_END();

public:
    test_convert_from_string();
    virtual ~test_convert_from_string();
    void setUp();
    void tearDown();

private:
    void testConvert_from_string();

};

#endif /* TEST_CONVERT_FROM_STRING_H */

