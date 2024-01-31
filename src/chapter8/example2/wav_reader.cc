// wav_reader.cc

#include <fstream>
#include <ios>
#include <algorithm>
#include <spdlog/spdlog.h>
#include "wav_reader.hh"

using boost::filesystem::directory_iterator;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::min;
using std::ios_base;

bool hasExtension(const string& filename, const string& s) {
    string ext{"." + s};
    if (ext.length() > filename.length()) return false;
    return 0 == filename.compare(filename.length() - ext.length(), ext.length(), ext);
}

struct RiffHeader {
    int8_t id[4];
    uint32_t length;
    int8_t format[4];
};

struct FormatSubchunkHeader {
    int8_t id[4];
    uint32_t subchunkSize;
};

struct FormatSubchunk {
    uint16_t formatTag;
    uint16_t channels;
    uint32_t samplesPerSecond;
    uint32_t averageBytesPerSecond;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

struct FactOrData {
    int8_t tag[4];
};

struct DataChunk {
    uint32_t length;
};

struct FactChunk {
    uint32_t chunkSize;
    uint32_t samplesPerChannel;
};

WavReader::WavReader(const std::string& source, const std::string& dest) 
    : source_(source)
    , dest_(dest) {
    descriptor_ = new WavDescriptor(dest);

    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("hello");
    spdlog::debug("reading from {} writing to {}", source, dest);
}

WavReader::~WavReader() {
    delete descriptor_;
}

void WavReader::publishSnippets() {
    directory_iterator itEnd; 
    for (directory_iterator it(source_); it != itEnd; ++it) 
        if (!is_directory(it->status()) && 
//  it->path().filename().string()=="husten.wav" &&
            hasExtension(it->path().filename().string(), "wav"))
            open(it->path().filename().string(), false);
}

string WavReader::toString(int8_t* bytes, unsigned int size) {
    return string{(char*)bytes, size};
}

void WavReader::writeSamples(
    ofstream& out, char* data, uint32_t startingSample,
    uint32_t samplesToWrite, uint32_t bytesPerSample
) const {
}


void WavReader::open(const std::string& name, bool trace) {
    spdlog::debug("opening {}", name);

    ifstream file{name, ios::in | ios::binary};
    if (!file.is_open()) {
        spdlog::error("unable to read {}", name);
        return;
    }

    ofstream out{dest_ + "/" + name, ios::out | ios::binary};

    RiffHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(RiffHeader));

    if (toString(header.id, 4) != "RIFF") {
        spdlog::error("{} is not a RIFF file", name);
        return;
    }
    if (toString(header.format, 4) != "WAVE") {
        spdlog::error("{} is not a wav file: {}", name, toString(header.format, 4));
        return;
    }
    out.write(reinterpret_cast<char*>(&header), sizeof(RiffHeader));

    FormatSubchunkHeader formatSubchunkHeader;
    file.read(reinterpret_cast<char*>(&formatSubchunkHeader), 
              sizeof(FormatSubchunkHeader));

    if (toString(formatSubchunkHeader.id, 4) != "fmt ") {
        spdlog::error("{} expecting 'fmt' for subchunk header; got '{}'",
                      name, toString(formatSubchunkHeader.id, 4));
        return;
    }

    out.write(reinterpret_cast<char*>(&formatSubchunkHeader), 
              sizeof(FormatSubchunkHeader));

    FormatSubchunk formatSubchunk;
    file.read(reinterpret_cast<char*>(&formatSubchunk), sizeof(FormatSubchunk));

    out.write(reinterpret_cast<char*>(&formatSubchunk), sizeof(FormatSubchunk));

    spdlog::debug("format tag: {}", formatSubchunk.formatTag);
    spdlog::debug("samples per second: {}", formatSubchunk.samplesPerSecond);
    spdlog::debug("channels: {}", formatSubchunk.channels);
    spdlog::debug("bits per sample: {}", formatSubchunk.bitsPerSample);

    auto bytes = formatSubchunkHeader.subchunkSize - sizeof(FormatSubchunk);

    auto additionalBytes = new char[bytes];
    file.read(additionalBytes, bytes);
    out.write(additionalBytes, bytes);
   
    FactOrData factOrData;
    file.read(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));
    out.write(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));

    if (toString(factOrData.tag, 4) == "fact") {
        FactChunk factChunk;
        file.read(reinterpret_cast<char*>(&factChunk), sizeof(FactChunk));
        out.write(reinterpret_cast<char*>(&factChunk), sizeof(FactChunk));

        file.read(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));
        out.write(reinterpret_cast<char*>(&factOrData), sizeof(FactOrData));

        spdlog::debug("samples per channel: {}", factChunk.samplesPerChannel);
    }

    if (toString(factOrData.tag, 4) != "data") {
        string tag{toString(factOrData.tag, 4)};
        spdlog::error("{}: unknown tag>{}<", name, tag);
        return;
    }

    DataChunk dataChunk;
    file.read(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

    spdlog::debug("riff header size = {}", sizeof(RiffHeader));
    spdlog::debug("subchunk header size = {}", sizeof(FormatSubchunkHeader));
    spdlog::debug("subchunk size = {}", formatSubchunkHeader.subchunkSize);
    spdlog::debug("data length = {}", dataChunk.length);
    
    // TODO if odd there is a padding byte!
    auto data = new char[dataChunk.length];
    file.read(data, dataChunk.length);
    file.close();

    // all of it
//   out.write(data, dataChunk.length);
    // TODO: multiple channels
    uint32_t secondsDesired{10};
    if (formatSubchunk.bitsPerSample == 0) formatSubchunk.bitsPerSample = 8;
    uint32_t bytesPerSample{formatSubchunk.bitsPerSample / uint32_t{8}};
    uint32_t samplesToWrite{secondsDesired * formatSubchunk.samplesPerSecond};
    uint32_t totalSamples{dataChunk.length / bytesPerSample};

    samplesToWrite = min(samplesToWrite, totalSamples);

    uint32_t totalSeconds{totalSamples / formatSubchunk.samplesPerSecond};
    spdlog::debug("total seconds {}", totalSeconds);

    dataChunk.length = samplesToWrite * bytesPerSample;
    out.write(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

    uint32_t startingSample{
        totalSeconds >= 10 ? 10 * formatSubchunk.samplesPerSecond : 0};

    writeSamples(out, data, startingSample, samplesToWrite, bytesPerSample);
    
    spdlog::debug("writing {} samples", samplesToWrite);
    for (auto sample = startingSample; 
         sample < startingSample + samplesToWrite; 
         sample++) {
        auto byteOffsetForSample = sample * bytesPerSample;
        for (uint32_t byte{0}; byte < bytesPerSample; byte++) 
            out.put(data[byteOffsetForSample + byte]);
    }
    spdlog::debug("completed writing {}", name);
    descriptor_->add(dest_, name, 
                     totalSeconds, formatSubchunk.samplesPerSecond, formatSubchunk.channels);
    out.close();
}

void WavReader::seekToEndOfHeader(ifstream& file, int subchunkSize) {
    auto bytes = subchunkSize - sizeof(FormatSubchunk) + 1;
    file.seekg(bytes, ios_base::cur);
}
