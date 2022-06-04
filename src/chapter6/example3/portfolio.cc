#include "portfolio.hh"

Portfolio::Portfolio(): shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return shareCount_ == 0u;
}

void Portfolio::purchase(const std::string& symbol, unsigned int shareCount) {
    if (shareCount == 0) throw InvalidPurchaseException();
    
    shareCount_ = shareCount;
}

void Portfolio::sell(const std::string& symbol, unsigned int shareCount) {
}


unsigned int Portfolio::shareCount(const std::string& symbol) const {
    return shareCount_;
}
