#include <iostream>
#include "place_description_service.hh"

using std::string;

string PlaceDescriptionService::response_("");

PlaceDescriptionService::PlaceDescriptionService() {
}

string PlaceDescriptionService::summaryDescription(
    const string& latitude, const string& longitude
) const {
    std::cout << "inside summaryDescription" << std::endl;

    response_ = "";
    auto url = createGetRequestUrl(latitude, longitude);
    
    return "";
}

string PlaceDescriptionService::createGetRequestUrl(
    const string& latitude, const string& longitude
) const {
    return "";
}
