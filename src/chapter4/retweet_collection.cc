#include "retweet_collection.hh"

bool RetweetCollection::isEmpty() {
    return tweets.empty();
}

void RetweetCollection::add(Tweet t) {
    tweets.push_back(t);
}

int RetweetCollection::size() {
    return tweets.size();
}
