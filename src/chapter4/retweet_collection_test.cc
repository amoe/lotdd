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


TEST_F(RetweetCollectionTest, HasSizeOfOneAfterTweetAdded) {
    collection.add(Tweet());

    ASSERT_THAT(collection.size(), Eq(1));
}

// Note that we pick the name of the test to describe the effective contents
// of the given fixture.
class RetweetCollectionContainingOneTweetTest: public Test {
public:
    RetweetCollection collection;
    // We store this so we can duplicate it later in a test.
    Tweet* tweet;   

    void SetUp() override {
        tweet = new Tweet("msg", "@user");
        collection.add(*tweet);
    }

    void TearDown() override {
        delete tweet;
        tweet = nullptr;   // not sure why this is here
    }
};

TEST_F(RetweetCollectionContainingOneTweetTest, IsNoLongerEmpty) {
    ASSERT_THAT(collection.isEmpty(), Eq(false));
}

TEST_F(RetweetCollectionContainingOneTweetTest, HasSizeOfOne) {
    ASSERT_THAT(collection.size(), Eq(1));
}

TEST_F(RetweetCollectionContainingOneTweetTest, IgnoresDuplicateTweetAdded) {
    Tweet duplicate(*tweet);
    collection.add(duplicate);
    ASSERT_THAT(collection.size(), Eq(1));
}
