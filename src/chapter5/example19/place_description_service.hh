#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <memory>
#include "http.hh"
#include "http_factory.hh"

class PlaceDescriptionService {
public:
    PlaceDescriptionService(std::shared_ptr<HttpFactory> httpFactory);
    
    std::string summaryDescription(
        const std::string& latitude, const std::string& longitude
    ) const;

private:
    std::string get(const std::string& url) const;
    std::string summaryDescription(const std::string& response) const;
    std::string createGetRequestUrl(const std::string& latitude, const std::string& longitude) const;
    std::string keyValue(const std::string& key, const std::string& value) const;
    
    std::shared_ptr<HttpFactory> httpFactory_;
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
