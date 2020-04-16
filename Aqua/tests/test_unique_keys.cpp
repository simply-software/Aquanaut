#include <set>
#include <vector>
#include "test_unique_keys.h"
#include "../datetime.h"
#include "../unique_keys.h"

CPPUNIT_TEST_SUITE_REGISTRATION(test_unique_keys);

test_unique_keys::test_unique_keys() {
    // Nothing to do
}

test_unique_keys::~test_unique_keys() {
    // Nothing to do
}

void test_unique_keys::setUp() {
    // Nothing to do
}

void test_unique_keys::tearDown() {
    // Nothing to do
}

struct unique_date {
    unique_date(const aqua::datetime_t& dt) : m_date(dt.get_date()) {}
    bool operator<(const unique_date& rhs) const noexcept { return m_date < rhs.m_date; }
    aqua::date_t m_date;
};

void test_unique_keys::testMethod() {
    { // Simple case
        std::vector<aqua::datetime_t> v = { };
        std::set<unique_date> result = aqua::unique_keys<unique_date>(v);
        CPPUNIT_ASSERT(result.size() == 0);
    }

    // case - everything in same partition
    // case - 2 partitions
    // case - input empty

}
