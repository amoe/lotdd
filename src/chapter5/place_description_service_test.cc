#include <gmock/gmock.h>
#include "http.hh"
#include "place_description_service.hh"

using std::to_string;
using namespace testing;

class PlaceDescriptionServiceTest: public Test {
public:
    static constexpr double VALID_LATITUDE = 50.824920;
    static constexpr double VALID_LONGITUDE = -0.155813;
};


class HttpStub: public Http {
public:
    MOCK_METHOD0(initialize, void());
    MOCK_CONST_METHOD1(get, string(const string&));
};

const string jsonResponse = R"({"address": {"road": "21 Fake Street", "city": "Brighton", "state": "East Sussex", "country": "GB"}})";

TEST_F(PlaceDescriptionServiceTest, MakesHttpRequestToObtainAddress) {
    HttpStub httpStub;
    
    string expectedUrl = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&lat=50.824920&lon=-0.155813";

    // Arrange...
    EXPECT_CALL(httpStub, get(expectedUrl)).WillOnce(Return(jsonResponse));

    PlaceDescriptionService service(&httpStub);

    // Act
    service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    // Explicit assert just to check.
    Mock::VerifyAndClearExpectations(&httpStub);
}

TEST_F(PlaceDescriptionServiceTest, FormatsRetrievedAddressIntoSummaryDescription) {
    HttpStub httpStub;

    EXPECT_CALL(httpStub, get(_)).WillOnce(Return(jsonResponse));

    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    ASSERT_THAT(description, Eq("21 Fake Street, Brighton, East Sussex, GB"));
}
