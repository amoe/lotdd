#include <memory>
#include "http.hh"
#include "curl_http.hh"
#include "http_factory.hh"

using std::shared_ptr;
using std::make_shared;

HttpFactory::HttpFactory() {
    reset();
}

shared_ptr<Http> HttpFactory::get() {
    return instance;
}

void HttpFactory::reset() {
    instance = make_shared<CurlHttp>();
}

void HttpFactory::setInstance(shared_ptr<Http> newInstance) {
    instance = newInstance;
}
