#include <string>
#include "place_description_service.hh"

using std::string;
using std::shared_ptr;

string PlaceDescriptionService::get(const string& url) const {
    auto http = httpService();
    http->initialize();
    return http->get(url);
}

shared_ptr<Http> PlaceDescriptionService::httpService() const {
    return make_shared<CurlHttp>();
}
