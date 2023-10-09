#include "purchase_record.hh"

bool operator==(const PurchaseRecord& lhs, const PurchaseRecord& rhs) {
    return lhs.shareDelta == rhs.shareDelta && lhs.date == rhs.date;
}
