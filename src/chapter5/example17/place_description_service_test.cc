#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "place_description_service.hh"
#include "http.hh"

using std::string;
using std::shared_ptr;

using testing::Test;
using testing::Eq;
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
    PlaceDescriptionService service;
    string description = service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    // Because the road and city aren't populated any more, we expect empty
    // strings in their place.
    ASSERT_THAT(description, Eq(", , Colorado, United States of America"));
}
