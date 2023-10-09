#include <vector>
#include <gmock/gmock.h>
#include "holding.hh"
#include "purchase_record.hh"

using testing::Test;
using testing::Eq;
using std::vector;


class HoldingTest: public Test {
};



TEST_F(HoldingTest, answersEmptyPurchaseRecordVectorWhenSymbolNotFound) {
    Holding holding;
    vector<PurchaseRecord> empty;
    ASSERT_THAT(holding.purchases(), Eq(empty));
}
