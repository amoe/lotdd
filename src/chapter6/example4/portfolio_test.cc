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
    ASSERT_THROW(portfolio.purchase(stockSymbol1, 0u), InvalidPurchaseException);
}

TEST_F(PortfolioTest, answersShareCountForAppropriateSymbol) {
    portfolio.purchase("AAPL", 2u);
    portfolio.purchase("IBM", 1u);
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(2u));
}

TEST_F(PortfolioTest, shareCountReflectsAccumulatedPurchasesOfSameSymbol) {
    portfolio.purchase(stockSymbol1, 1u);
    portfolio.purchase(stockSymbol1, 2u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(3u));
}

TEST_F(PortfolioTest, reducesShareCountOfSymbolOnSell) {
    portfolio.purchase(stockSymbol1, 1u);
    portfolio.sell(stockSymbol1, 1u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(0u));
}

TEST_F(PortfolioTest, throwsWhenSellingMoreSharesThanPurchased) {
    portfolio.purchase(stockSymbol1, 1u);
    ASSERT_THROW(portfolio.sell(stockSymbol1, 2u), InvalidSellException);
}


TEST_F(PortfolioTest, answersThePurchaseRecordForASinglePurchase) {
    portfolio.purchase(stockSymbol1, 1u);
    auto purchases = portfolio.purchases(stockSymbol1);

    auto thePurchase = purchases.at(0);
    
    ASSERT_THAT(thePurchase.shareCount, Eq(1u));
    ASSERT_THAT(thePurchase.date, Eq(Portfolio::FIXED_PURCHASE_DATE));
                
    ASSERT_THROW(portfolio.sell(stockSymbol1, 2u), InvalidSellException);
}


