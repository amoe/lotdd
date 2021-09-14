#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include <memory>
#include "http.hh"

class PlaceDescriptionService {
    virtual ~PlaceDescriptionService() { }

private:
    std::string get(const std::string& url) const;

protected:
    virtual std::shared_ptr<Http> httpService() const;
};


#endif /* PLACE_DESCRIPTION_SERVICE_HH */
