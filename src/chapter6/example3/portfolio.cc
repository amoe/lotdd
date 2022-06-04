#include "portfolio.hh"
#include <stdexcept>
#include <iostream>
#include <ostream>

using std::runtime_error;
using std::cout;
using std::endl;

Portfolio::Portfolio(): shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return shareHoldings.empty();
}

void Portfolio::purchase(const std::string& symbol, unsigned int purchaseCount) {
    if (purchaseCount == 0) throw InvalidPurchaseException();

    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        shareHoldings.insert({symbol, purchaseCount});
    } else {
        it->second = it->second + purchaseCount;
    }
}

void Portfolio::sell(const std::string& symbol, unsigned int sellCount) {
}


unsigned int Portfolio::shareCount(const std::string& symbol) const {
    auto it = shareHoldings.find(symbol);
    if (it == shareHoldings.end()) {
        return 0u;
    } else {
        return it->second;
    }
}
