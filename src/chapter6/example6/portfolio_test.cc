#include <gmock/gmock.h>
#include "portfolio.hh"
#include <string>
#include <boost/date_time/gregorian/gregorian_types.hpp>

using testing::Test;
using testing::Eq;
using std::string;
using boost::gregorian::date;

class PortfolioTest: public Test {
public:
    static const string stockSymbol1;
    static const string stockSymbol2;
    Portfolio portfolio;

    void purchaseHelper(
        const string& symbol,
        unsigned int shareCount,
        const date& transactionDate=Portfolio::FIXED_PURCHASE_DATE
    );
};

const string PortfolioTest::stockSymbol1{"IBM"};
const string PortfolioTest::stockSymbol2{"SSNLF"};    // Samsung

void PortfolioTest::purchaseHelper(
    const string& symbol, unsigned int shareCount, const date& transactionDate
) {
    portfolio.purchase(symbol, shareCount, transactionDate);
}
    


TEST_F(PortfolioTest, answersZeroForShareCountOfUnpurchaseHelperdSymbol) {
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(0u));
}

TEST_F(PortfolioTest, isNotEmptyAfterPurchaseHelper) {
    purchaseHelper(stockSymbol1, 1u);
    ASSERT_FALSE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, answersShareCountForPurchaseHelperdSymbol) {
    purchaseHelper(stockSymbol1, 2u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(2u));
}


TEST_F(PortfolioTest, throwsOnPurchaseHelperOfZeroShares) {
    ASSERT_THROW(purchaseHelper(stockSymbol1, 0u), InvalidPurchaseException);
}

TEST_F(PortfolioTest, answersShareCountForAppropriateSymbol) {
    purchaseHelper("AAPL", 2u);
    purchaseHelper("IBM", 1u);
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(2u));
}

TEST_F(PortfolioTest, shareCountReflectsAccumulatedPurchaseHelpersOfSameSymbol) {
    purchaseHelper(stockSymbol1, 1u);
    purchaseHelper(stockSymbol1, 2u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(3u));
}

TEST_F(PortfolioTest, reducesShareCountOfSymbolOnSell) {
    purchaseHelper(stockSymbol1, 1u);
    portfolio.sell(stockSymbol1, 1u);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(0u));
}

TEST_F(PortfolioTest, throwsWhenSellingMoreSharesThanPurchaseHelperd) {
    purchaseHelper(stockSymbol1, 1u);
    ASSERT_THROW(portfolio.sell(stockSymbol1, 2u), InvalidSellException);
}


TEST_F(PortfolioTest, answersThePurchaseRecordForASinglePurchase) {
    date dateOfPurchase{2014, 03, 17};
    portfolio.purchase(stockSymbol2, 5, dateOfPurchase);
    
    auto purchases = portfolio.purchases(stockSymbol2);

    auto thePurchase = purchases.at(0);
    
    ASSERT_THAT(thePurchase.shareCount, Eq(5u));
    ASSERT_THAT(thePurchase.date, Eq(dateOfPurchase));
}


