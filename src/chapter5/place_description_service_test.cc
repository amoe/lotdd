#include <gmock/gmock.h>

using namespace testing;

TEST(MyComponent, ActsAsIExpect) {
    ASSERT_THAT(2 + 2, Eq(4));
}

