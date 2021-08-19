#include <gmock/gmock.h>
#include <memory>
#include "tweet.hh"
#include "retweet_collection.hh"

using namespace ::testing;

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;

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
    unique_ptr<Tweet> tweet;   

    void SetUp() override {
        tweet = make_unique<Tweet>("msg", "@user");
        collection.add(*tweet);
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
