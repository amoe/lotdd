#include <numeric>
#include "holding.hh"

using std::vector;
using std::accumulate;

void Holding::add(const PurchaseRecord& record) {
    purchaseRecords.push_back(record);
}

vector<PurchaseRecord> Holding::purchases() const {
    return purchaseRecords;
}

int doAddition(int total, const PurchaseRecord& b) {
    return total + b.shareDelta;
}

int Holding::shareCount() const {
    return accumulate(
        purchaseRecords.begin(), purchaseRecords.end(), 0, doAddition
    );
}

