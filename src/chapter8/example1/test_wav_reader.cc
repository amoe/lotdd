#include <gmock/gmock.h>
#include "wav_reader.hh"

using testing::Test;
using testing::Eq;

TEST(MyComponent, ActsAsIExpect) {
    WavReader reader("foo", "bar");

//    reader.open("foo", true);
    
    ASSERT_THAT(2 + 2, Eq(4));
}

