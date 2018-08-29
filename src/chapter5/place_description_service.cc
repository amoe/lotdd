#include "place_description_service.hh"
#include "address_extractor.hh"

using std::to_string;

// This isn't really Meyers-compliant, because it's using a static utility method
// where a free (namespaced) function would do.
string PlaceDescriptionService::keyValue(const string& key, const string& value) const {
    return key + "=" + value;
}

string PlaceDescriptionService::createGetRequestUrl(double latitude, double longitude) const {
    string server{"http://open.mapquestapi.com/"};
    string document{"nominatim/v1/reverse"};

    return server + document + "?" + keyValue("format", "json") 
        + "&" + keyValue("lat", to_string(latitude)) + "&" + keyValue("lon", to_string(longitude));
}

string PlaceDescriptionService::summaryDescription(double latitude, double longitude) {
    string urlPrefix("http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");

    string getRequestUrl
        = createGetRequestUrl(latitude, longitude);

    auto jsonResponse = http->get(getRequestUrl);
    
    AddressExtractor extractor;
    auto address = extractor.addressFrom(jsonResponse);

    string result = address.road + ", " + address.city + ", " + address.state + ", " + address.country;
    return result;
}
