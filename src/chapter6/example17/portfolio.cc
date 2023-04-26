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
    throwIfShareCountIsZero(shareChange);
    updateShareCount(symbol, shareChange);
    addPurchaseRecord(symbol, shareChange, transactionDate);
}

// I definitely would not have gone this far in abstracting out small methods,
// IMO this is introducing cognitive load, but we're following Langr's lead here
void Portfolio::throwIfShareCountIsZero(int shareChange) const {
    if (shareChange == 0)
        throw ShareCountCannotBeZeroException();
}

void Portfolio::updateShareCount(const string& symbol, int shareChange) {
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        // In the case of a sell, we will never reach this point, because the
        // guard clause prevents us.
        shareHoldings.insert({symbol, shareChange});
    } else {
        it->second = it->second + shareChange;
    }
}

void Portfolio::addPurchaseRecord(const std::string& symbol, int shareChange, const date& transactionDate) {
    auto record = PurchaseRecord(shareChange, transactionDate);
    purchaseRecords[symbol].push_back(record);
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
        throw InsufficientSharesException();

    transact(symbol, -sellCount, transactionDate);
}


int Portfolio::shareCount(const std::string& symbol) const {
    return find(shareHoldings, symbol);
}

vector<PurchaseRecord> Portfolio::purchases(const string& symbol) const {
    return find(purchaseRecords, symbol);
}
