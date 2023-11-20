#include <gmock/gmock.h>
#include <string>
#include "line_reader.hh"

using testing::Test;
using testing::Eq;
using std::string;


void ASSERT_EQ_WITH_LENGTH(
    const char* expected, const char* actual, unsigned length
) {
    ASSERT_EQ(length, strlen(actual));
    ASSERT_STREQ(expected, actual);
}

class LineReaderTest: public Test {
public:
    const char* line;
    unsigned len;
};

static int writeTemporaryFile(const string& content) {
    FILE* temporaryFile = tmpfile();
    int fileDescriptor = fileno(temporaryFile);
    write(fileDescriptor, content.c_str(), 1);
    lseek(fileDescriptor, 0, SEEK_SET);
    return fileDescriptor;
}

TEST_F(LineReaderTest, oneLine) {
    LineReader reader(writeTemporaryFile("a"));
    
    ASSERT_TRUE(reader.getNextLine(&line, &len));

    ASSERT_EQ_WITH_LENGTH("a", line, len);
    
    reader.popLine(len);

    ASSERT_FALSE(reader.getNextLine(&line, &len));
}
