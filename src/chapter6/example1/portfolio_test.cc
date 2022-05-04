#include <gmock/gmock.h>
#include "portfolio.hh"

using testing::Test;
using testing::Eq;

class PortfolioTest: public Test {
public:
    Portfolio portfolio;
};


TEST_F(PortfolioTest, answersZeroForShareCountOfUnpurchasedSymbol) {
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(0u));
}

TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}
