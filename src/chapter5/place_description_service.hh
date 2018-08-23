#ifndef PLACE_DESCRIPTION_SERVICE_HH
#define PLACE_DESCRIPTION_SERVICE_HH

#include "http.hh"

using std::string;

class PlaceDescriptionService {
public:
    PlaceDescriptionService(Http* http) : http(http) { }
    string summaryDescription(double latitude, double longitude);

private:
    Http* http;
};

#endif /* PLACE_DESCRIPTION_SERVICE_HH */
