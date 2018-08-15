#ifndef TWEET_HH
#define TWEET_HH

#include <string>

using std::string;

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
