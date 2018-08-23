#include <gmock/gmock.h>

using namespace testing;

class HttpStub: public Http {
    void initialize() override {}
    
    std::string get(const std::string& url) const override {
        return "???";
    }
};


TEST_F(PlaceDescriptionServiceTest, ReturnsDescriptionForValidLocation) {
    HttpStub httpStub;

    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

    ASSERT_THAT(description, Eq("21 Fake Street"));
}

