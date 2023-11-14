#include <string>
#include <cstring>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "line_reader.hh"

using boost::iostreams::file_descriptor_source;
using boost::iostreams::never_close_handle;
using boost::iostreams::stream;
using std::getline;
using std::string;
using std::memcpy;

bool LineReader::getNextLine(const char** line, unsigned int* len) {
    file_descriptor_source fdSource{fd, never_close_handle};
    stream<file_descriptor_source> fileStream{fdSource};


    string theLine;
    getline(fileStream, theLine);
    
    int length = theLine.length();

    // Testing just eof() is not enough here as we can reach the end of file
    // after a "good" read.
    if (length == 0 && fileStream.eof())
        return false;

    
    int lengthWithNul = theLine.length() + 1;
    
    buffer = new char[lengthWithNul];
    memcpy(buffer, theLine.c_str(), lengthWithNul);

    *line = buffer;
    *len = length;

    return true;
}


// In this implementation we need to free the memory
void LineReader::popLine(unsigned int len) const {
    delete buffer;
}
