#include <iostream>
#include <cstring>
#include "place_description_service.hh"
#include "mapquest_api_key.hh"

using std::string;

string PlaceDescriptionService::response_("");
char PlaceDescriptionService::errorBuffer[CURL_ERROR_SIZE];

PlaceDescriptionService::PlaceDescriptionService(): curl(NULL) {
    // potentially do some curl initialization here
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(
        curl, CURLOPT_ERRORBUFFER, errorBuffer
    );
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION, &PlaceDescriptionService::writeCallback
    );
}

// XXX: MUST BE DECLARED AS STATIC!  Otherwise this will be called wrong by Curl.
size_t PlaceDescriptionService::writeCallback(
    const char* buf, size_t size, size_t nMemb, void* userData
) {
    std::cout << "inside write callback" << std::endl;
    // Bit worried about the efficiency of this.
    // NB this segfaults for whatever reason...
    for (auto i = 0u; i < size * nMemb; i++) {
        response_.push_back(buf[i]);
    }

    std::cout << "wrote everything" << std::endl;
    
    return size * nMemb;
}


string PlaceDescriptionService::summaryDescription(
    const string& latitude, const string& longitude
) const {
    std::cout << "inside summaryDescription" << std::endl;

    response_ = "";
    auto url = createGetRequestUrl(latitude, longitude);

    std::cout << "requesting " << url << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << "wrote value '" << response_ << "'" << std::endl;

    // Value location;
    // Reader reader;
    // reader.parse(response_, location);
    
    return "";
}

string PlaceDescriptionService::createGetRequestUrl(
    const string& latitude, const string& longitude
) const {
    string server{"http://open.mapquestapi.com/"};
    string document{"nominatim/v1/reverse"};
    return server + document + "?" +
        keyValue("format", "json") + "&" +
        keyValue("lat", latitude) + "&" +
        keyValue("lon", longitude) + "&" +
        keyValue("key", MAPQUEST_API_KEY);
}

string PlaceDescriptionService::keyValue(
    const string& key, const string& value
) const {
    return key + "=" + value;
}
