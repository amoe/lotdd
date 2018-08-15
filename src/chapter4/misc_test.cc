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

TEST(MiscTest, IntersectionMatchers) {
    string actual = string("al") + "pha";
    ASSERT_THAT(
        actual,
        AllOf(StartsWith("al"), EndsWith("ha"), Ne("aloha"))
    );
}

TEST(MiscTest, ComparingFloats) {
    double x{4.0};
    double y{0.56};

    // Will fail due to FP inaccuracy.
    //ASSERT_THAT(x + y, Eq(4.56));

    // Will use ULPs to get loose-EQ to a sensible tolerance.
    ASSERT_THAT(x + y, DoubleEq(4.56));
}
