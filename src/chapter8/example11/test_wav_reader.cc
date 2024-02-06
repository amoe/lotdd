#include <sstream>
#include <gmock/gmock.h>
#include "wav_reader.hh"

using std::ostringstream;
using testing::Test;
using testing::Eq;

class WavReaderTest: public Test {
public:
    WavReader reader{"", ""};
    ostringstream out;
};

TEST_F(WavReaderTest, writesSingleSample) {
    char data[] { "abcd" };

    uint32_t bytesPerSample{1};
    uint32_t startingSample{0};
    uint32_t samplesToWrite{1};

    reader.writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

    ASSERT_THAT("a", Eq(out.str()));
}

TEST_F(WavReaderTest, writesMultibyteSampleFromMiddle) {
    char data[] { "0123456789ABCDEFG" };
    uint32_t bytesPerSample{2};
    uint32_t startingSample{4};
    uint32_t samplesToWrite{3};

    reader.writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

    ASSERT_THAT("89ABCD", Eq(out.str()));
}

TEST_F(WavReaderTest, incorporatesChannelCount) {
    char data[] { "0123456789ABCDEFG" };

    uint32_t bytesPerSample{2};
    uint32_t startingSample{0};
    uint32_t samplesToWrite{2};
    uint32_t channels{2};

    reader.writeSamples(
        &out, data, startingSample, samplesToWrite, bytesPerSample,
        channels
    );
    
    ASSERT_THAT("01234567", Eq(out.str()));
}
