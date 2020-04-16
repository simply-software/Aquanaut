#pragma once

#include <cppunit/extensions/HelperMacros.h>

class test_unique_keys : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(test_unique_keys);

    CPPUNIT_TEST(testMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    test_unique_keys();
    virtual ~test_unique_keys();
    void setUp();
    void tearDown();

private:
    void testMethod();
};

