#include <string>

class Portfolio {
public:
    Portfolio();

    bool isEmpty() const;
//    void purchase(const std::string& symbol, unsigned int shareCount);

    unsigned int shareCount(const std::string& symbol) const;
    

private:
    bool isEmpty_;
    unsigned int shareCount_;
};

