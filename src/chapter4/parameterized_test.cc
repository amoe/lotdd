#include <gmock/gmock.h>
#include "adder.hh"

using namespace testing;

// 
struct SumCase {
    int a;
    int b;
    int expected;

    SumCase(int a, int b, int expected): a(a), b(b), expected(expected) {
    }
};

class MyParameterizedTest: public TestWithParam<SumCase> {
};

TEST(NonParameterizedTest, GeneratesASumFromTwoNumbers) {
    ASSERT_THAT(Adder::sum(1, 1), Eq(2));
}

TEST_P(MyParameterizedTest, GeneratesLotsOfSumsFromTwoNumbers) {
    SumCase input = GetParam();

    ASSERT_THAT(Adder::sum(input.a, input.b), Eq(input.expected));
}

SumCase sums[] = {
    SumCase(1, 1, 2),
    SumCase(1, 2, 3),
    SumCase(2, 2, 4),
};

INSTANTIATE_TEST_CASE_P(BulkTest, MyParameterizedTest, ValuesIn(sums));
