#include <string>

class InvalidPurchaseException: public std::exception {
};


class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
    void purchase(const std::string& symbol, unsigned int shareCount);

    unsigned int shareCount(const std::string& symbol) const;
    

private:
    unsigned int shareCount_;
};

