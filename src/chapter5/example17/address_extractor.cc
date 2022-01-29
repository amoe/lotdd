#include "address_extractor.hh"
#include "address.hh"

using std::string;


Address AddressExtractor::addressFrom(const string& json) const {
    Address address;
    Json::Value jsonAddress{jsonAddressFrom(json)};
    populate(address, jsonAddress);
    return address; 
}

void AddressExtractor::populate(Address& address, Json::Value& jsonAddress) const {
    address.road = getString(jsonAddress, "road");
    address.city = getString(jsonAddress, "city");
    address.state = getString(jsonAddress, "state");
    address.country = getString(jsonAddress, "country");
}


Json::Value AddressExtractor::parse(const std::string& json) const {
    Json::Value root;
    Json::Reader reader;

    reader.parse(json, root);
    return root;
}


Json::Value AddressExtractor::jsonAddressFrom(const string& json) const {
   auto location = parse(json);
   return location.get("address", Json::Value::null);
}


string AddressExtractor::getString(Json::Value& result, const string& name) const {
    return result.get(name, "").asString();
}
