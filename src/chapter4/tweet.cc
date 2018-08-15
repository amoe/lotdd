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
        throw InvalidUserException(user);
    }
}


const string Tweet::getBody() {
    return body;
}

const string Tweet::getUser() {
    return user;
}
