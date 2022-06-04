#include "portfolio.hh"
#include <stdexcept>

using std::runtime_error;

Portfolio::Portfolio(): shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return shareHoldings.empty();
}

void Portfolio::purchase(const std::string& symbol, unsigned int purchaseCount) {
    if (purchaseCount == 0) throw InvalidPurchaseException();

    unsigned int existingCount = this->shareCount(symbol);
    shareHoldings.insert({symbol, existingCount + purchaseCount});
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
