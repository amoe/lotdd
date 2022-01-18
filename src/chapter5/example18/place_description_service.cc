#include <string>
#include "place_description_service.hh"
#include "http.hh"
#include "curl_http.hh"
#include "address_extractor.hh"
#include "address.hh"
#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;

// Override Getter means the initialization code does get invoked by the tests.
PlaceDescriptionService::PlaceDescriptionService(): http_(make_shared<CurlHttp>()) {
}

string PlaceDescriptionService::get(const string& url) const {
    auto http = httpService();
    http->initialize();
    return http->get(url);
}

// Override Getter: just return our previously instantiated stubbable thing.
shared_ptr<Http> PlaceDescriptionService::httpService() const {
    return http_;
}

string PlaceDescriptionService::summaryDescription(const string& response) const {
    AddressExtractor extractor;
    auto address = extractor.addressFrom(response);
    return address.summaryDescription();
}

string PlaceDescriptionService::summaryDescription(
    const string& latitude, const string& longitude
) const {
    auto request = createGetRequestUrl(latitude, longitude);
    auto response = get(request);
    return summaryDescription(response);
}

string PlaceDescriptionService::createGetRequestUrl(
      const string& latitude, const string& longitude) const {
    string server{"http://open.mapquestapi.com/"};
    string document{"nominatim/v1/reverse"};
    return server + document + "?" +
        keyValue("format", "json") + "&" +
        keyValue("lat", latitude) + "&" +
        keyValue("lon", longitude);
}


string PlaceDescriptionService::keyValue(const string& key, const string& value) const {
    return key + "=" + value;
}
