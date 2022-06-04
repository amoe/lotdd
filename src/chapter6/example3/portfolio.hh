#include <string>
#include <unordered_map>

class InvalidPurchaseException: public std::exception {
};

class InvalidSellException: public std::exception {
};


class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
    void purchase(const std::string& symbol, unsigned int shareCount);
    void sell(const std::string& symbol, unsigned int shareCount);
    unsigned int shareCount(const std::string& symbol) const;
    

private:
    unsigned int shareCount_;
    std::unordered_map<std::string, int> shareHoldings;
};

