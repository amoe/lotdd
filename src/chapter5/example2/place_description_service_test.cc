#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "place_description_service.hh"
#include "http.hh"

using std::string;
using std::shared_ptr;

using testing::Test;
using testing::InSequence;

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};


class PlaceDescriptionService_StubHttpService: public PlaceDescriptionService {
public:
    PlaceDescriptionService_StubHttpService(shared_ptr<HttpStub> httpStub): httpStub(httpStub) {
    }

    // Override Factory Method pattern.  We override httpService() to return a
    // specific stub version.
    shared_ptr<Http> httpService() const override {
        return httpStub;
    }


    shared_ptr<Http> httpStub;
};

class PlaceDescriptionServiceTest: public Test {
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;
};

// Very annoyingly, you can't initialize these strings in the class def.
const string PlaceDescriptionServiceTest::VALID_LATITUDE{"38.005"};
const string PlaceDescriptionServiceTest::VALID_LONGITUDE{"-104.44"};


TEST_F(PlaceDescriptionServiceTest, makesHttpRequestToObtainAddress) {
    InSequence forceExpectationOrder;
    shared_ptr<HttpStub> httpStub{new HttpStub};

    string urlStart{"http://open.mapquestapi.com/nominatim/v/reverse?format=json&"};

    auto expectedUrl = urlStart
        + "lat=" + VALID_LATITUDE + "&lon=" + VALID_LONGITUDE;

    // Set up the expected calls.
    // We expect that asking for the summary description associated with a given
    // latitude and longitude will end up invoking methods on the stub (because
    // we overrode the httpService() method.)
    EXPECT_CALL(*httpStub, initialize());
    EXPECT_CALL(*httpStub, get(expectedUrl));

    PlaceDescriptionService_StubHttpService service{httpStub};
    
    service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
}
