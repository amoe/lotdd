#ifndef PURCHASE_RECORD_HH
#define PURCHASE_RECORD_HH

#include <boost/date_time/gregorian/gregorian_types.hpp>


struct PurchaseRecord {
    PurchaseRecord(
        int shareDelta, boost::gregorian::date date
    ): shareDelta(shareDelta), date(date) {}
    
    int shareDelta;    // can be both positive and negative
    boost::gregorian::date date;
};

bool operator==(const PurchaseRecord& lhs, const PurchaseRecord& rhs);

#endif /* PURCHASE_RECORD_HH */
