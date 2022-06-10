#include <string>
#include <unordered_map>
#include <vector>

class InvalidPurchaseException: public std::exception {
};

class InvalidSellException: public std::exception {
};

struct PurchaseRecord {
    PurchaseRecord(
        unsigned int shareCount, std::string date
    ): shareCount(shareCount), date(date) {}
    
    unsigned int shareCount;
    std::string date;
};


class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
    void purchase(const std::string& symbol, unsigned int shareCount);
    void sell(const std::string& symbol, unsigned int shareCount);
    unsigned int shareCount(const std::string& symbol) const;
    std::vector<PurchaseRecord> purchases(const std::string& symbol) const;

    static const std::string FIXED_PURCHASE_DATE;

private:
    unsigned int shareCount_;
    std::unordered_map<std::string, unsigned int> shareHoldings;

    std::vector<PurchaseRecord> purchaseRecords;
};
