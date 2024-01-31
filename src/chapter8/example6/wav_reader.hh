#ifndef WAV_READER_HH
#define WAV_READER_HH

#include <fstream>
#include <boost/filesystem.hpp>
#include <string>
#include "wav_descriptor.hh"

bool hasExtension(const std::string& text, const std::string& substring);

class WavReader {
public:
    WavReader(const std::string& source, const std::string& dest);
    virtual ~WavReader();
    void open(const std::string& name, bool trace);
    void list(
        const boost::filesystem::path& dir, 
        const std::string &filename, 
        std::vector<boost::filesystem::path>& found) const;
    void listAll() const;
    void publishSnippets();

    void writeSamples(
        std::ostream* out, char* data, uint32_t startingSample,
        uint32_t samplesToWrite, uint32_t bytesPerSample
    ) const;

    
private:
    WavDescriptor* descriptor_;

    void seekToEndOfHeader(std::ifstream& file, int headerLength);
    std::string toString(int8_t* c, unsigned int size);

    std::string source_;
    std::string dest_;
};

#endif /* WAV_READER_HH */
