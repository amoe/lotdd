#ifndef TWEET_HH
#define TWEET_HH

#include <stdexcept>
#include <string>

using std::string;
using std::invalid_argument;

class InvalidUserException: public invalid_argument {
public:
    InvalidUserException(const string& user): invalid_argument(user) {}
};

class Tweet {
public:
    Tweet();
    Tweet(const string& body, const string& user);
    
    const string getBody();
    const string getUser();

private:
    const string body;
    const string user;
};

#endif /* TWEET_HH */
