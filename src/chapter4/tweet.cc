#include <stdexcept>
#include "tweet.hh"

using std::runtime_error;

bool isValid(const string& user) {
    return user.at(0) == '@';
}

Tweet::Tweet() {
}


Tweet::Tweet(const string& body, const string& user)  : body(body), user(user) {
    if (!isValid(user)) {
        throw std::runtime_error("invalid user");
    }
}


const string Tweet::getBody() {
    return body;
}

const string Tweet::getUser() {
    return user;
}
