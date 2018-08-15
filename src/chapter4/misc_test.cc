#include <string>
#include <gmock/gmock.h>

using namespace testing;
using std::string;

TEST(MiscTest, BasicHamcrest) {
    string actual = string("al") + "pha";
    ASSERT_THAT(actual, Eq("alpha"));
}

TEST(MiscTest, HamcrestMatchers) {
    string actual = string("al") + "pha";
    ASSERT_THAT(actual, StartsWith("al"));
}

