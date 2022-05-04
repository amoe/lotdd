#include "portfolio.hh"

Portfolio::Portfolio(): isEmpty_(true), shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return isEmpty_;
}

void Portfolio::purchase(const std::string& symbol, unsigned int shareCount) {
    isEmpty_ = false;
    shareCount_ = shareCount;
}

unsigned int Portfolio::shareCount(const std::string& symbol) const {
    return shareCount_;
}
