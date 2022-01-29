#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "place_description_service.hh"
#include "http.hh"

using std::string;
using std::shared_ptr;

using testing::Test;
using testing::InSequence;

class PlaceDescriptionServiceTest: public Test {
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;
};

// Very annoyingly, you can't initialize these strings in the class def.
const string PlaceDescriptionServiceTest::VALID_LATITUDE{"38.005"};
const string PlaceDescriptionServiceTest::VALID_LONGITUDE{"-104.44"};


TEST_F(PlaceDescriptionServiceTest, makesHttpRequestToObtainAddress) {
    // InSequence forceExpectationOrder;
    // shared_ptr<HttpStub> httpStub{new HttpStub};

    PlaceDescriptionService service;

    string urlStart{"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};

    auto expectedUrl = urlStart
        + "lat=" + VALID_LATITUDE + "&lon=" + VALID_LONGITUDE;

    // EXPECT_CALL(*httpStub, initialize());
    // EXPECT_CALL(*httpStub, get(expectedUrl));

    // PlaceDescriptionService_StubHttpService service{httpStub};
    service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
}
