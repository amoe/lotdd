#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "http_factory.hh"
#include "place_description_service.hh"
#include "http.hh"

using std::string;
using std::shared_ptr;
using std::make_shared;

using testing::Test;
using testing::InSequence;

class HttpStub: public Http {
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};

class PlaceDescriptionServiceTest: public Test {
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;

    PlaceDescriptionServiceTemplate<HttpStub> service;
};

// Very annoyingly, you can't initialize these strings in the class def.
const string PlaceDescriptionServiceTest::VALID_LATITUDE{"38.005"};
const string PlaceDescriptionServiceTest::VALID_LONGITUDE{"-104.44"};

TEST_F(PlaceDescriptionServiceTest, makesHttpRequestToObtainAddress) {
    string urlStart{"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
    auto expectedUrl = urlStart
        + "lat=" + VALID_LATITUDE + "&lon=" + VALID_LONGITUDE;
    // Set up the expected calls.
    EXPECT_CALL(service.http(), initialize());
    EXPECT_CALL(service.http(), get(expectedUrl));
    service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
}
