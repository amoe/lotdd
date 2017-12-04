#include <gmock/gmock.h>


// import the test predicates to make the test read more fluently
using ::testing::Eq;

class Soundex {
public:
    std::string encode(const std::string& word) const {
        return "A";
    }
};

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    Soundex soundex;

    auto encoded = soundex.encode("A");

    ASSERT_THAT(encoded, Eq("A"));
}
