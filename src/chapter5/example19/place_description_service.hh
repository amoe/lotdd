#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <memory>
#include "http.hh"
#include "http_factory.hh"
#include "address_extractor.hh"

template<typename T>
class PlaceDescriptionServiceTemplate {
public:
    std::string summaryDescription(
        const std::string& latitude, const std::string& longitude
    ) const {
        auto request = createGetRequestUrl(latitude, longitude);
        auto response = get(request);
        return summaryDescription(response);
    }
    
    T& http() {
        return http_;
    }

private:
    std::string summaryDescription(const std::string& response) const {
        AddressExtractor extractor;
        auto address = extractor.addressFrom(response);
        return address.summaryDescription();
    }
    
    std::string get(const std::string& url) {
        http_.initialize();
        return http_.get(url);
    }

    std::string createGetRequestUrl(
        const std::string& latitude, const std::string& longitude
    ) const {
        std::string server{"http://open.mapquestapi.com/"};
        std::string document{"nominatim/v1/reverse"};
        return server + document + "?" +
            keyValue("format", "json") + "&" +
            keyValue("lat", latitude) + "&" +
            keyValue("lon", longitude);
    }


    std::string keyValue(
        const std::string& key, const std::string& value
     ) const {
        return key + "=" + value;
    }
    

    T http_;
};

class Http;
using PlaceDescriptionService = PlaceDescriptionServiceTemplate<Http>;

#endif /* PLACE_DESCRIPTION_SERVICE_HH */
