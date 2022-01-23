#ifndef HTTP_FACTORY_HH
#define HTTP_FACTORY_HH

#include "http.hh"

class HttpFactory {
public:
    HttpFactory();
    std::shared_ptr<Http> get();
    void reset();
    void setInstance(std::shared_ptr<Http> newInstance);

private:
    std::shared_ptr<Http> instance;
};

#endif /* HTTP_FACTORY_HH */
