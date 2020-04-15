#include <set>
#include <vector>
#include "test_partition.h"
#include "../datetime.h"
#include "../partition.h"

CPPUNIT_TEST_SUITE_REGISTRATION(test_partition);

test_partition::test_partition() {
}

test_partition::~test_partition() {
}

void test_partition::setUp() {
}

void test_partition::tearDown() {
}

struct unique_date {
    unique_date(const aqua::datetime_t& dt) : m_date(dt.get_date()) {}
    bool operator<(const unique_date& rhs) const noexcept { return m_date < rhs.m_date; }
    aqua::date_t m_date;
};

void test_partition::testMethod() {
    { // Simple case
        std::vector<aqua::datetime_t> v = { };
        std::set<unique_date> result = aqua::partition<unique_date>(v);
        CPPUNIT_ASSERT(result.size() == 0);
    }

    // case - everything in same partition
    // case - 2 partitions
    // case - input empty

}

void test_partition::testFailedMethod() {
}

