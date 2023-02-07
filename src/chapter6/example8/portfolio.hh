#include <string>
#include <unordered_map>
#include <vector>
#include <boost/date_time/gregorian/gregorian_types.hpp>

class InvalidPurchaseException: public std::exception {
};

class InvalidSellException: public std::exception {
};

struct PurchaseRecord {
    PurchaseRecord(
        int shareDelta, boost::gregorian::date date
    ): shareDelta(shareDelta), date(date) {}
    
    int shareDelta;    // can be both positive and negative
    boost::gregorian::date date;
};


class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
    
    void purchase(
        const std::string& symbol,
        int shareCount,
        const boost::gregorian::date& transactionDate
    );
    
    void sell(
        const std::string& symbol,
        int shareCount,
        const boost::gregorian::date& transactionDate
    );
    
    int shareCount(const std::string& symbol) const;
    std::vector<PurchaseRecord> purchases(const std::string& symbol) const;

    static const boost::gregorian::date FIXED_PURCHASE_DATE;

private:
    int shareCount_;
    std::unordered_map<std::string, int> shareHoldings;

    std::vector<PurchaseRecord> purchaseRecords;
};
