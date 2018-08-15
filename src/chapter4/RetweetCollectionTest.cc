#include <gmock/gmock.h>
#include "tweet.hh"
#include "retweet_collection.hh"

using namespace ::testing;

class RetweetCollectionTest: public Test {
public:
    RetweetCollection collection;
};

TEST_F(RetweetCollectionTest, IsEmptyWhenCreated) {
    ASSERT_THAT(collection.isEmpty(), Eq(true));
}


TEST_F(RetweetCollectionTest, IsNoLongerEmptyAfterTweetAdded) {
    collection.add(Tweet());

    ASSERT_THAT(collection.isEmpty(), Eq(false));
}

