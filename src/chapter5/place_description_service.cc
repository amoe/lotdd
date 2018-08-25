#include "place_description_service.hh"
#include "address_extractor.hh"

using std::to_string;

string PlaceDescriptionService::summaryDescription(double latitude, double longitude) {
    string getRequestUrl
        = "lat=" + to_string(latitude) + "&lon=" + to_string(longitude);

    auto jsonResponse = http->get(getRequestUrl);
    
    AddressExtractor extractor;
    auto address = extractor.addressFrom(jsonResponse);

    string result = address.road + ", " + address.city + ", " + address.state + ", " + address.country;
    return result;
}
