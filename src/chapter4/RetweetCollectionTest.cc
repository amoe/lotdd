#include <gmock/gmock.h>
#include "tweet.hh"
#include "retweet_collection.hh"

using namespace ::testing;

class RetweetCollectionTest: public Test {
};

TEST(RetweetCollectionTest, IsEmptyWhenCreated) {
    RetweetCollection collection;
    ASSERT_THAT(collection.isEmpty(), Eq(true));
}


TEST(RetweetCollectionTest, IsNoLongerEmptyAfterTweetAdded) {
    RetweetCollection collection;

    collection.add(Tweet());

    ASSERT_THAT(collection.isEmpty(), Eq(false));
}

