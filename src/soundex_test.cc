#include <gmock/gmock.h>


// import the test predicates to make the test read more fluently
using ::testing::Eq;

class Soundex {
public:
    std::string encode(const std::string& word) const {
        return zeroPad(word);
    }
private:
    std::string zeroPad(const std::string& word) const {
        return word + "000";
    }
};

// Declare a fixture, which is just a class.
class SoundexEncoding : public testing::Test {
public:
    Soundex soundex;
};

// Now we can use the public member of the class to store persistent state.
TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    auto encoded = soundex.encode("A");

    ASSERT_THAT(encoded, Eq("A000"));
}

// now we declare another test in the same file to handle the padding case.

TEST(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    auto encoded = soundex.encode("I");

    ASSERT_THAT(encoded, Eq("I000"));
}
