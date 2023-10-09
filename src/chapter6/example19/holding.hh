#include <vector>
#include "purchase_record.hh"

class Holding {
public:
    void add(const PurchaseRecord& record);
    std::vector<PurchaseRecord>  purchases() const;

private:
    std::vector<PurchaseRecord> purchaseRecords;
};
