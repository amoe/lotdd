#include <gmock/gmock.h>
#include "portfolio.hh"
#include <string>

using testing::Test;
using testing::Eq;
using std::string;

class PortfolioTest: public Test {
public:
    static const string stockSymbol1;
    Portfolio portfolio;
};

const string PortfolioTest::stockSymbol1{"IBM"};


TEST_F(PortfolioTest, answersZeroForShareCountOfUnpurchasedSymbol) {
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(0u));
}

TEST_F(PortfolioTest, isNotEmptyAfterPurchase) {
    portfolio.purchase(stockSymbol1, 1u);
    ASSERT_FALSE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, answersShareCountForPurchasedSymbol) {
    portfolio.purchase(stockSymbol1, 2u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(2u));
}


TEST_F(PortfolioTest, throwsOnPurchaseOfZeroShares) {
    ASSERT_THROW(portfolio.purchase(stockSymbol1, 0), InvalidPurchaseException);
}

TEST_F(PortfolioTest, answersShareCountForAppropriateSymbol) {
}

TEST_F(PortfolioTest, shareCountReflectsAccumulatedPurchasesOfSameSymbol) {
}

TEST_F(PortfolioTest, reducesShareCountOfSymbolOnSell) {
}

TEST_F(PortfolioTest, throwsWhenSellingMoreSharesThanPurchased) {
}


