/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   test_partition.h
 * Author: Jay
 *
 * Created on Apr 15, 2020, 10:09:56 AM
 */

#ifndef TEST_PARTITION_H
#define TEST_PARTITION_H

#include <cppunit/extensions/HelperMacros.h>

class test_partition : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_partition);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    test_partition();
    virtual ~test_partition();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* TEST_PARTITION_H */

