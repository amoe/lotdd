#include <gmock/gmock.h>
#include "http.hh"
#include "place_description_service.hh"

using namespace testing;

class HttpStub: public Http {
    void initialize() override {}
    
    std::string get(const std::string& url) const override {
        return R"({"address": {"road": "21 Fake Street", "city": "Brighton", "state": "East Sussex", "country": "GB"}})";
    }
};

class PlaceDescriptionServiceTest: public Test {
};


TEST_F(PlaceDescriptionServiceTest, ReturnsDescriptionForValidLocation) {
    HttpStub httpStub;

    PlaceDescriptionService service(&httpStub);


    double validLatitude = 50.824920;
    double validLongitude = -0.155813;


    auto description = service.summaryDescription(validLatitude, validLongitude);

    ASSERT_THAT(description, Eq("21 Fake Street, Brighton, East Sussex, GB"));
}

