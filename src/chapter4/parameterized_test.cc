#include <gmock/gmock.h>
#include "adder.hh"

using namespace testing;

TEST(ParameterizedTest, GeneratesASumFromTwoNumbers) {
    ASSERT_THAT(Adder::sum(1, 1), Eq(2));
}
