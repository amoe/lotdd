#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <memory>
#include "curl_http.hh"

class PlaceDescriptionService {
    virtual ~PlaceDescriptionService() { }

protected:
    virtual std::shared_ptr<Http> httpService() const;
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
