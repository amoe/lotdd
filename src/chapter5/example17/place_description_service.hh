#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <string>
#include <curl/curl.h>

class PlaceDescriptionService {
public:
    PlaceDescriptionService();
    virtual ~PlaceDescriptionService() { }

    std::string summaryDescription(
        const std::string& latitude, const std::string& longitude
    ) const;

private:
    std::string createGetRequestUrl(
        const std::string& latitude, const std::string& longitude
    ) const;

    
    std::string keyValue(
        const std::string& key, const std::string& value
    ) const;

    // Must fulfil signature of CURLOPT_WRITEFUNCTION.
    // XXX: const?
    size_t writeCallback(
        const char* buf, size_t size, size_t nMemb, void* userData
    );


    // ???
    static std::string response_;
    static char errorBuffer[];
    CURL* curl;
    
protected:
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
