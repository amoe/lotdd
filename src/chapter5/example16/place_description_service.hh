#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <memory>
#include "http.hh"

class PlaceDescriptionService {
public:
    PlaceDescriptionService();
    virtual ~PlaceDescriptionService() { }

    std::string summaryDescription(
        const std::string& latitude, const std::string& longitude
    ) const;

private:
    std::string get(const std::string& url) const;
    std::string summaryDescription(const std::string& response) const;
    std::string createGetRequestUrl(const std::string& latitude, const std::string& longitude) const;
    std::string keyValue(const std::string& key, const std::string& value) const;
    
    std::shared_ptr<Http> http_;
    
protected:
    virtual std::shared_ptr<Http> httpService() const;
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
