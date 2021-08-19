#ifndef HTTP_HH
#define HTTP_HH

#include <string>

using std::string;

class Http {
public:
    virtual ~Http() {}
    virtual void initialize() = 0;
    virtual string get(const string& url) const = 0;
};


#endif /* HTTP_HH */
