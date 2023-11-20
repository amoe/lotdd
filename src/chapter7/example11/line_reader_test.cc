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
    write(fileDescriptor, content.c_str(), content.length());
    lseek(fileDescriptor, 0, SEEK_SET);
    return fileDescriptor;
}

TEST_F(LineReaderTest, updatesLineAndLenOnRead) {
    LineReader reader(writeTemporaryFile("a"));
    reader.getNextLine(&line, &len);
    ASSERT_EQ_WITH_LENGTH("a", line, len);
}

TEST_F(LineReaderTest, answersTrueWhenLineAvailable) {
    LineReader reader(writeTemporaryFile("a"));
    bool wasRead = reader.getNextLine(&line, &len);
    ASSERT_TRUE(wasRead);
}

TEST_F(LineReaderTest, answersFalseWhenAtEof) {
    LineReader reader(writeTemporaryFile("a"));
    reader.getNextLine(&line, &len);
    reader.popLine(len);

    bool wasRead = reader.getNextLine(&line, &len);
    ASSERT_FALSE(wasRead);
}


TEST_F(LineReaderTest, advancesToNextLineAfterPop) {
    LineReader reader(writeTemporaryFile("a\nb"));
    reader.getNextLine(&line, &len);
    reader.popLine(len);
    reader.getNextLine(&line, &len);
    ASSERT_EQ_WITH_LENGTH("b", line, len);
}



// If we don't pop the line, it should just keep returning the same line.
TEST_F(LineReaderTest, repeatedlyReturnsCurrentRecord) {
    LineReader reader(writeTemporaryFile("a\nb"));
    reader.getNextLine(&line, &len);
    ASSERT_EQ_WITH_LENGTH("a", line, len);
    reader.getNextLine(&line, &len);
    ASSERT_EQ_WITH_LENGTH("a", line, len);
}


