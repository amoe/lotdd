#include <string>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "line_reader.hh"

using boost::iostreams::file_descriptor_source;
using boost::iostreams::never_close_handle;
using boost::iostreams::stream;

bool LineReader::getNextLine(const char** line, unsigned int* len) const {
    file_descriptor_source foo{fd, never_close_handle};
    stream<file_descriptor_source> bar{foo};
    
    
    return false;
}

void LineReader::popLine(unsigned int len) const {
}
