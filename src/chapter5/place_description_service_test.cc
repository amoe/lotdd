#include <gmock/gmock.h>

using namespace testing;

TEST_F(PlaceDescriptionServiceTest, ReturnsDescriptionForValidLocation) {
    HttpStub httpStub;

    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

    ASSERT_THAT(description, Eq("21 Fake Street"));
}

