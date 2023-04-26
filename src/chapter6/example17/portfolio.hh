#include <string>
#include <unordered_map>
#include <vector>
#include <boost/date_time/gregorian/gregorian_types.hpp>

    

class InvalidPurchaseException: public std::exception {
};

class ShareCountCannotBeZeroException: public std::exception {
};

class InsufficientSharesException: public std::exception {
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
    // Find a value in a map, or return the empty initialization of that value.
    template <typename T> T find(
        std::unordered_map<std::string, T> theMap,
        const std::string& key
    ) const {
        auto it = theMap.find(key);
        if (it == theMap.end()) {
            return T{};
        } else {
            return it->second;
        }
    }
    
    void transact(
        const std::string& symbol,
        int shareCount,
        const boost::gregorian::date& transactionDate
    );

    void throwIfShareCountIsZero(int shareChange) const;
    void updateShareCount(const std::string&, int);
    void addPurchaseRecord(const std::string&, int, const boost::gregorian::date&);

    
    int shareCount_;
    std::unordered_map<std::string, int> shareHoldings;

    std::unordered_map<std::string, std::vector<PurchaseRecord>> purchaseRecords;
};
