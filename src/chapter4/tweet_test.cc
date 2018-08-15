#include <string>
#include <gmock/gmock.h>
#include "tweet.hh"

using std::string;
using namespace testing;

TEST(TweetTest, RequiresUserToStartWithAtSign) {
    string invalidUser("notStartingWith@");

    // Kind of insane
    ASSERT_ANY_THROW(
        Tweet tweet("msg", invalidUser)
    );
}


TEST(TweetTest, RequiresUserToStartWithAtSignAndThrowsCorrectException) {
    string invalidUser("notStartingWith@");

    // Kind of insane
    ASSERT_THROW(
        Tweet tweet("msg", invalidUser),
        InvalidUserException
    );
}

