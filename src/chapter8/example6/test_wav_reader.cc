#include <sstream>
#include <gmock/gmock.h>
#include "wav_reader.hh"

using std::ostringstream;
using testing::Test;
using testing::Eq;

class WavReaderTest: public Test {
public:
    ostringstream out;
};

TEST_F(WavReaderTest, writesSingleSample) {
    char data[] { "abcd" };
    WavReader reader("foo", "bar");

    uint32_t bytesPerSample{1};
    uint32_t startingSample{0};
    uint32_t samplesToWrite{1};

    reader.writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

    ASSERT_THAT("a", Eq(out.str()));
}

