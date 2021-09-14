#include <string>
#include "place_description_service.hh"
#include "http.hh"
#include "curl_http.hh"

using std::string;
using std::shared_ptr;
using std::make_shared;

string PlaceDescriptionService::get(const string& url) const {
    auto http = httpService();
    http->initialize();
    return http->get(url);
}

shared_ptr<Http> PlaceDescriptionService::httpService() const {
    return make_shared<CurlHttp>();
}
