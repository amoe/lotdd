#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "place_description_service.hh"
#include "http.hh"

using std::string;
using std::shared_ptr;

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};


class PlaceDescriptionService_StubHttpService: public PlaceDescriptionService {
public:
    PlaceDescriptionService_StubHttpService(shared_ptr<HttpStub> httpStub): httpStub(httpStub) {
    }

    shared_ptr<Http> httpService() const override {
        return httpStub;
    }


    shared_ptr<Http> httpStub;
};
