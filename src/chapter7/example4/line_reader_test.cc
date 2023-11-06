#include <gmock/gmock.h>
#include "line_reader.hh"

using testing::Test;
using testing::Eq;

static int writeTemporaryFile() {
    FILE* temporaryFile = tmpfile();
    int fileDescriptor = fileno(temporaryFile);
    write(fd, "a", 1);
    lseek(fd, 0, SEEK_SET);
    return fileDescriptor;
}

TEST(LineReaderTest, oneLine) {
    const int fd = writeTemporyFile("a");

    LineReader reader(fd);
    const char* line;
    unsigned int len;
    
    ASSERT_TRUE(reader.getNextLine(&line, &len));

    ASSERT_EQ(len, (unsigned) 1);
    ASSERT_EQ(line[0], 'a');
    ASSERT_EQ(line[1], 0);
    
    reader.popLine(len);

    ASSERT_FALSE(reader.getNextLine(&line, &len));

    close(fd);
}
