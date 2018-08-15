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


TEST(TweetTest, RequiresUserToStartWithAtSignAndExceptionContainsCorrectValue) {
    string invalidUser("notStartingWith@");

    // You can also use this somewhat-less-magical format.
    try {
        Tweet tweet("msg", invalidUser);
        FAIL();
    } catch (const InvalidUserException& expected) {
        // We HAVE to use ASSERT_STREQ() here because .what() uses C-strings,
        // which are incompatible with Eq()
        // This is because what() has to be guaranteed to not throw exceptions
        // itself.
        ASSERT_STREQ("notStartingWith@", expected.what());
    }
}

