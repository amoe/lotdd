#include <gmock/gmock.h>
#include "soundex.hh"

using namespace testing;

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

// 
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
    // Because there are multiple consonants that are touched by the
    // specification of this behaviour, we break the "One Assert per Test" rule.
    // Using EXPECT_THAT we specify that the other assertions should still run
    // even if this one fails.
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
}
