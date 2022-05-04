#include "portfolio.hh"

Portfolio::Portfolio(): isEmpty_(true), shareCount_(0u) { }

bool Portfolio::isEmpty() const {
    return isEmpty_;
}

unsigned int Portfolio::shareCount(const std::string& symbol) const {
    return shareCount_;
}
