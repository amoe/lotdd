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
    void initialize() override {}
    
    std::string get(const std::string& url) const override {
        verify(url);
        return R"({"address": {"road": "21 Fake Street", "city": "Brighton", "state": "East Sussex", "country": "GB"}})";
    }

    void verify(const string& url) const  {
        string urlStart("http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");

        string expectedArgs(
            urlStart + "lat=" + to_string(PlaceDescriptionServiceTest::VALID_LATITUDE)
            + "&lon=" + to_string(PlaceDescriptionServiceTest::VALID_LONGITUDE)
        );

        ASSERT_THAT(url, EndsWith(expectedArgs));
    }
};



TEST_F(PlaceDescriptionServiceTest, ReturnsDescriptionForValidLocation) {
    HttpStub httpStub;

    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    ASSERT_THAT(description, Eq("21 Fake Street, Brighton, East Sussex, GB"));
}

