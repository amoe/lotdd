#include <algorithm>
#include "retweet_collection.hh"

bool RetweetCollection::isEmpty() {
    return tweets.empty();
}

void RetweetCollection::add(Tweet tweet) {
    // This could be std::find or std::find_if.  not very OO to use accessors
    // in this way
    for (Tweet t : tweets) {
        if (t.getBody() == tweet.getBody() && t.getUser() == tweet.getUser())
            return;
    }

    tweets.push_back(tweet);
}

int RetweetCollection::size() {
    return tweets.size();
}
