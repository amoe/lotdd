// wav_reader.cc

#include <fstream>
#include <ios>
#include <spdlog/spdlog.h>
#include "wav_reader.hh"

using std::string;
using std::ifstream;
using std::ios;

void WavReader::open(const string& name, bool trace) {
//    rLog(channel, "opening %s", name.c_str());
    spdlog::info("Welcome to spdlog!");
    
    // ifstream file{name, ios::in | ios::binary};
    // if (!file.is_open()) {
    // }
}
