#include "portfolio.hh"
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian_types.hpp>

using std::runtime_error;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using boost::gregorian::date;

const date Portfolio::FIXED_PURCHASE_DATE{date{1970, 1, 1}};

Portfolio::Portfolio(): shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return shareHoldings.empty();
}

void Portfolio::transact(
    const std::string& symbol,
    int shareChange,
    const date& transactionDate
) {
    if (shareChange == 0)
        throw ShareCountCannotBeZeroException();
    
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        // In the case of a sell, we will never reach this point, because the
        // guard clause prevents us.
        shareHoldings.insert({symbol, shareChange});
    } else {
        it->second = it->second + shareChange;
    }

    // XXX: probably needs to be renamed to reflect fact that it's no longer
    // purely purchases
    purchaseRecords.push_back(PurchaseRecord(shareChange, transactionDate));
}

void Portfolio::purchase(
    const std::string& symbol,
    int purchaseCount,
    const date& transactionDate
) {
    transact(symbol, purchaseCount, transactionDate);
}

void Portfolio::sell(
    const std::string& symbol,
    int sellCount,
    const date& transactionDate
) {
    if (sellCount > shareCount(symbol))
        throw InvalidSellException();

    transact(symbol, -sellCount, transactionDate);
}


int Portfolio::shareCount(const std::string& symbol) const {
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        return 0;
    } else {
        return it->second;
    }
}

vector<PurchaseRecord> Portfolio::purchases(const string& symbol) const {
    return purchaseRecords;
}
