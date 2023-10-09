#include "holding.hh"

using std::vector;

void Holding::add(const PurchaseRecord& record) {
    purchaseRecords.push_back(record);
}

vector<PurchaseRecord> Holding::purchases() const {
    return purchaseRecords;
}
