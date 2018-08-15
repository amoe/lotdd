#ifndef RETWEET_COLLECTION_HH
#define RETWEET_COLLECTION_HH

#include <vector>
#include "tweet.hh"

using std::vector;

class RetweetCollection {
public:
    bool isEmpty();
    void add(Tweet t);

private:
    vector<Tweet> tweets;
};

#endif /* RETWEET_COLLECTION_HH */
