#include <gmock/gmock.h>

using testing::Test;
using testing::Eq;

TEST(LineReaderTest, oneLine) {
    ASSERT_THAT(2+2, Eq(4));
}
