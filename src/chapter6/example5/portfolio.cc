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

void Portfolio::purchase(
    const std::string& symbol,
    unsigned int purchaseCount,
    const date& transactionDate
) {
    if (purchaseCount == 0) throw InvalidPurchaseException();

    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        shareHoldings.insert({symbol, purchaseCount});
    } else {
        it->second = it->second + purchaseCount;
    }

    purchaseRecords.push_back(PurchaseRecord(purchaseCount, FIXED_PURCHASE_DATE));
}

void Portfolio::sell(const std::string& symbol, unsigned int sellCount) {
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
//        throw InvalidSellException
    } else {
        if (sellCount > it->second) {
            throw InvalidSellException();
        } else {
            it->second = it->second - sellCount;
        }
    }
}


unsigned int Portfolio::shareCount(const std::string& symbol) const {
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        return 0u;
    } else {
        return it->second;
    }
}

vector<PurchaseRecord> Portfolio::purchases(const string& symbol) const {
    return purchaseRecords;
}
