#include "portfolio.hh"
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <numeric>
#include <boost/date_time/gregorian/gregorian_types.hpp>

using std::runtime_error;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::accumulate;
using boost::gregorian::date;

const date Portfolio::FIXED_PURCHASE_DATE{date{1970, 1, 1}};

Portfolio::Portfolio() { }

bool Portfolio::isEmpty() const {
    // XXX: surely this won't handle the case where you buy a share then sell it
    return holdings.empty();
}

void Portfolio::transact(
    const std::string& symbol,
    int shareChange,
    const date& transactionDate
) {
    throwIfShareCountIsZero(shareChange);
    addPurchaseRecord(symbol, shareChange, transactionDate);
}

// I definitely would not have gone this far in abstracting out small methods,
// IMO this is introducing cognitive load, but we're following Langr's lead here
void Portfolio::throwIfShareCountIsZero(int shareChange) const {
    if (shareChange == 0)
        throw ShareCountCannotBeZeroException();
}

void Portfolio::addPurchaseRecord(const std::string& symbol, int shareChange, const date& transactionDate) {
    if (!containsSymbol(symbol)) {
        initializePurchaseRecords(symbol);
    }

    add(symbol, {shareChange, transactionDate});
}

bool Portfolio::containsSymbol(const string& symbol) const {
    return holdings.find(symbol) != holdings.end();
}

void Portfolio::initializePurchaseRecords(const string& symbol) {
    holdings.insert({symbol, Holding()});
}


void Portfolio::add(const string& symbol, PurchaseRecord&& record) {
    holdings[symbol].add(record);
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
    auto it = holdings.find(symbol);

    if (it == holdings.end()) {
        return 0;
    } else {
        return it->second.shareCount();
    }
}

vector<PurchaseRecord> Portfolio::purchases(const string& symbol) const {
    return find(holdings, symbol).purchases();
}
