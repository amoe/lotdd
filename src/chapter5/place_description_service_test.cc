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




TEST_F(PlaceDescriptionServiceTest, MakesHttpRequestToObtainAddress) {
    HttpStub httpStub;
    
    string expectedUrl = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&lat=50.824920&lon=-0.155813";

    // Arrange...
    EXPECT_CALL(httpStub, get(expectedUrl));

    PlaceDescriptionService service(&httpStub);

    // Act
    service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    ASSERT_THAT(2 + 2, Eq(4));

    Mock::VerifyAndClearExpectations(&httpStub);
}
