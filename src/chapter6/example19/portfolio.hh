#include <string>
#include <unordered_map>
#include <vector>
#include "purchase_record.hh"   // temporary
#include "holding.hh"

class InvalidPurchaseException: public std::exception {
};

class ShareCountCannotBeZeroException: public std::exception {
};

class InsufficientSharesException: public std::exception {
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

    bool containsSymbol(const std::string& symbol) const;
    void initializePurchaseRecords(const std::string& symbol);
    void add(const std::string& symbol, PurchaseRecord&& record);
    
    std::unordered_map<std::string, std::vector<PurchaseRecord>> purchaseRecords;

    std::unordered_map<std::string, Holding> holdings;
};
