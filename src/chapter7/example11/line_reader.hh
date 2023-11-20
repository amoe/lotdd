#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>

class LineReader {
public:
    LineReader(const int fd);
    ~LineReader();

    bool getNextLine(const char** line, unsigned int* len);

    void popLine(unsigned int len);

private:
    // These must be stored at the instance level otherwise they won't
    // preserve the state of the eof flag across calls.
    
    boost::iostreams::stream<boost::iostreams::file_descriptor_source> fileStream;

    int fd;
    char* buffer = nullptr;
    int lastReadLength;
};

