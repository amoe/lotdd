#include <vector>
#include "purchase_record.hh"

class Holding {
public:
    void add(const PurchaseRecord& record);
    std::vector<PurchaseRecord>  purchases() const;
    int shareCount() const;

private:
    std::vector<PurchaseRecord> purchaseRecords;
};
