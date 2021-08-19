#include "place_description_service.hh"
#include "address_extractor.hh"

using std::to_string;

string PlaceDescriptionService::keyValue(const string& key, const string& value) const {
    return key + "=" + value;
}


string PlaceDescriptionService::summaryDescription(double latitude, double longitude) {
    string server = "http://open.mapquestapi.com/";
    string document = "nominatim/v1/reverse";
    string url = server + document + "?" + keyValue("format", "json")
        + "&" + keyValue("lat", to_string(latitude)) + "&"
        + keyValue("lon", to_string(longitude));

    http->initialize();
    auto response = http->get(url);

    AddressExtractor extractor;

    auto address = extractor.addressFrom(response);
    string result = address.road + ", " + address.city + ", " + address.state + ", " + address.country;
    return result;
}
