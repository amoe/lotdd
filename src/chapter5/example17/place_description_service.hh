#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <string>

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


    // ???
    static std::string response_;
    
protected:
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
