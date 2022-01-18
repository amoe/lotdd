#ifndef ADDRESS_EXTRACTOR_HH
#define ADDRESS_EXTRACTOR_HH

#include <json/reader.h>
#include "address.hh"

class AddressExtractor {
public:
    Address addressFrom(const std::string& json) const;

private:
    Json::Value jsonAddressFrom(const std::string& json) const;
    void populate(Address& address, Json::Value& jsonAddress) const;
    Json::Value parse(const std::string& json) const;
    std::string getString(Json::Value& result, const std::string& name) const;
};

#endif /* ADDRESS_EXTRACTOR_HH */
