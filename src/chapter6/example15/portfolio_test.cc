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
        int shareCount,
        const date& transactionDate=Portfolio::FIXED_PURCHASE_DATE
    );

    void sellHelper(
        const string& symbol,
        int shareCount,
        const date& transactionDate=Portfolio::FIXED_PURCHASE_DATE
    );

    
    void assertPurchase(
        const PurchaseRecord& thePurchase,
        int shareCount,
        const date& transactionDate
    ) {
        ASSERT_THAT(thePurchase.shareDelta, Eq(shareCount));
        ASSERT_THAT(thePurchase.date, Eq(transactionDate));
    }
};

const string PortfolioTest::stockSymbol1{"IBM"};
const string PortfolioTest::stockSymbol2{"SSNLF"};    // Samsung

void PortfolioTest::purchaseHelper(
    const string& symbol, int shareCount, const date& transactionDate
) {
    portfolio.purchase(symbol, shareCount, transactionDate);
}

void PortfolioTest::sellHelper(
    const string& symbol, int shareCount, const date& transactionDate
) {
    portfolio.sell(symbol, shareCount, transactionDate);
}



TEST_F(PortfolioTest, answersZeroForShareCountOfUnpurchaseHelperdSymbol) {
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(0));
}

TEST_F(PortfolioTest, isNotEmptyAfterPurchaseHelper) {
    purchaseHelper(stockSymbol1, 1);
    ASSERT_FALSE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, isEmptyWhenCreated) {
    ASSERT_TRUE(portfolio.isEmpty());
}

TEST_F(PortfolioTest, answersShareCountForPurchasedSymbol) {
    purchaseHelper(stockSymbol1, 2);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(2));
}


TEST_F(PortfolioTest, throwsOnPurchaseOfZeroShares) {
    ASSERT_THROW(purchaseHelper(stockSymbol1, 0), ShareCountCannotBeZeroException);
}

TEST_F(PortfolioTest, throwsOnSellOfZeroShares) {
    ASSERT_THROW(sellHelper(stockSymbol1, 0), ShareCountCannotBeZeroException);
}

TEST_F(PortfolioTest, answersShareCountForAppropriateSymbol) {
    purchaseHelper("AAPL", 2);
    purchaseHelper("IBM", 1);
    ASSERT_THAT(portfolio.shareCount("AAPL"), Eq(2));
}

TEST_F(PortfolioTest, shareCountReflectsAccumulatedPurchaseHelpersOfSameSymbol) {
    purchaseHelper(stockSymbol1, 1);
    purchaseHelper(stockSymbol1, 2);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(3));
}

TEST_F(PortfolioTest, reducesShareCountOfSymbolOnSell) {
    purchaseHelper(stockSymbol1, 1);
    sellHelper(stockSymbol1, 1);
    ASSERT_THAT(portfolio.shareCount(stockSymbol1), Eq(0));
}

TEST_F(PortfolioTest, throwsWhenSellingMoreSharesThanPurchased) {
    purchaseHelper(stockSymbol1, 1);
    ASSERT_THROW(sellHelper(stockSymbol1, 2), InsufficientSharesException);
}


TEST_F(PortfolioTest, answersThePurchaseRecordForASinglePurchase) {
    date dateOfPurchase{2014, 03, 17};
    purchaseHelper(stockSymbol2, 5, dateOfPurchase);
    
    auto purchases = portfolio.purchases(stockSymbol2);

    assertPurchase(purchases.at(0), 5, dateOfPurchase);
}

TEST_F(PortfolioTest, includesSalesInPurchaseRecords) {
    purchaseHelper(stockSymbol2, 10);
    sellHelper(stockSymbol2, 5);

    auto sales = portfolio.purchases(stockSymbol2);
    assertPurchase(sales.at(1), -5, Portfolio::FIXED_PURCHASE_DATE);
}


