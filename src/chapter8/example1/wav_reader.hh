#ifndef WAV_READER_HH
#define WAV_READER_HH

#include <string>

class WavReader {
public:
    void open(const std::string& name, bool trace);
};

#endif /* WAV_READER_HH */
