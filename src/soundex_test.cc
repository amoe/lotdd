#include <gmock/gmock.h>

using namespace testing;

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
class SoundexEncoding : public Test {
public:
    Soundex soundex;
};

// Now we can use the public member of the class to store persistent state.
TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

// now we declare another test in the same file to handle the padding case.

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}
