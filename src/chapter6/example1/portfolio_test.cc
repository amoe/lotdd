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

TEST_F(PortfolioTest, IsNotEmptyAfterPurchase) {
    portfolio.purchase("IBM", 1u);
    ASSERT_FALSE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, answersShareCountForPurchasedSymbol) {
    portfolio.purchase("IBM", 2u);
    ASSERT_THAT(portfolio.shareCount("IBM"), Eq(2u));
}


