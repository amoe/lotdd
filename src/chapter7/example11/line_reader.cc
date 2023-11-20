#include <string>
#include <cstring>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "line_reader.hh"
#include <iostream>

using boost::iostreams::file_descriptor_source;
using boost::iostreams::never_close_handle;
using boost::iostreams::stream;
using std::getline;
using std::string;
using std::memcpy;
using std::cout;
using std::endl;

bool LineReader::getNextLine(const char** line, unsigned int* len) {
    if (buffer == nullptr) {
        string theLine;
        getline(fileStream, theLine);

        lastReadLength = theLine.length();

        // Testing just eof() is not enough here as we can reach the end of file
        // after a "good" read.
        if (lastReadLength == 0 && fileStream.eof()){
            return false;
        }
    
        int lengthWithNul = lastReadLength + 1;
    
        buffer = new char[lengthWithNul];
        memcpy(buffer, theLine.c_str(), lengthWithNul);

        *line = buffer;
        *len = lastReadLength;

        return true;
    } else {
        *line = buffer;
        *len = lastReadLength;
        return false;
    }
}


// In this implementation we need to free the memory
void LineReader::popLine(unsigned int len) {
    delete buffer;
    buffer = nullptr;
}

LineReader::LineReader(const int fd):
    fileStream{file_descriptor_source{fd, never_close_handle}}
    { }


LineReader::~LineReader() {
    close(fd);
}
