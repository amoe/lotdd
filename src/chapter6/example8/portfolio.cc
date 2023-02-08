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
    int purchaseCount,
    const date& transactionDate
) {
    if (purchaseCount < 1)
        throw ShareCountCannotBeZeroException();


    int shareChange = purchaseCount;
    
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        shareHoldings.insert({symbol, purchaseCount});
    } else {
        it->second = it->second + shareChange;
    }

    purchaseRecords.push_back(PurchaseRecord(shareChange, transactionDate));
}

void Portfolio::sell(
    const std::string& symbol,
    int sellCount,
    const date& transactionDate
) {
    if (sellCount < 1)
        throw ShareCountCannotBeZeroException();
    
    if (sellCount > shareCount(symbol))
        throw InvalidSellException();

    int shareChange = -sellCount;
    
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
//        throw InvalidSellException
    } else {
        if (sellCount > it->second) {
            throw InvalidSellException();
        } else {
            it->second = it->second + shareChange;
            purchaseRecords.push_back(PurchaseRecord(shareChange, transactionDate));
        }
    }
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
