#ifndef CURL_HTTP_HH
#define CURL_HTTP_HH

#include <curl/curl.h>
#include <string>
#include "http.hh"

class CurlHttp: public Http {
public:
    CurlHttp();
    virtual ~CurlHttp();

    void initialize();
    virtual std::string get(const std::string& url) const;
};


#endif /* CURL_HTTP_HH */
