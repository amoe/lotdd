#include "tweet.hh"

Tweet::Tweet() {
}


Tweet::Tweet(const string& body, const string& user)  : body(body), user(user) {
}

const string Tweet::getBody() {
    return body;
}

const string Tweet::getUser() {
    return user;
}
