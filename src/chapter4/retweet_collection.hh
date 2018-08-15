#ifndef RETWEET_COLLECTION_HH
#define RETWEET_COLLECTION_HH

#include "tweet.hh"

class RetweetCollection {
public:
    bool isEmpty();
    void add(Tweet t);
};

#endif /* RETWEET_COLLECTION_HH */
