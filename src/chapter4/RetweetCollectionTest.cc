#include <gmock/gmock.h>

using namespace ::testing;

class RetweetCollectionTest: public Test {
};

TEST(RetweetCollectionTest, ActsAsIExpect) {
    ASSERT_THAT(2 + 2, Eq(4));
}


TEST(ARetweetCollection, IncrementsSizeWhenTweetAdded) {
//    ASSERT_THAT(2 + 2, Eq(4));
}

