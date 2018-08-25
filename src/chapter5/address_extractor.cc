#include "address_extractor.hh"
#include "address.hh"
#include <jsoncpp/json/json.h>
#include <stdexcept>

Address AddressExtractor::addressFrom(string json) {
    // TODO: implement extractor using JsonCpp
    
    Address result;

    Json::Reader reader;
    Json::Value root;

    bool success = reader.parse(json, root, false);

    if (!success) {
        throw std::runtime_error("json parse failed");
    }

    auto addressObject = root["address"];

    result.road =  addressObject["road"].asString();
    result.city =  addressObject["city"].asString();
    result.state =  addressObject["state"].asString();
    result.country =  addressObject["country"].asString();

    return result;
}
