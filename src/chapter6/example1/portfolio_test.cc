#include <gmock/gmock.h>
#include "portfolio.hh"

using testing::Test;

class PortfolioTest: public Test {
public:
    Portfolio portfolio;
};


TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}
