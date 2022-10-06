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
        unsigned int shareCount, boost::gregorian::date date
    ): shareCount(shareCount), date(date) {}
    
    unsigned int shareCount;
    boost::gregorian::date date;
};


class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
    
    void purchase(
        const std::string& symbol,
        unsigned int shareCount,
        const boost::gregorian::date& transactionDate=Portfolio::FIXED_PURCHASE_DATE
    );
    
    void sell(const std::string& symbol, unsigned int shareCount);
    unsigned int shareCount(const std::string& symbol) const;
    std::vector<PurchaseRecord> purchases(const std::string& symbol) const;

    static const boost::gregorian::date FIXED_PURCHASE_DATE;

private:
    unsigned int shareCount_;
    std::unordered_map<std::string, unsigned int> shareHoldings;

    std::vector<PurchaseRecord> purchaseRecords;
};
