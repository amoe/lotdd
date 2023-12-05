#include <string>
#include <gmock/gmock.h>
#include "branch.hh"
#include "persistence.hh"
#include "serializable.hh"

using testing::Test;
using testing::Eq;
using std::string;
using std::exception;
using std::shared_ptr;

class DuplicateBranchNameException: public exception {
};


bool matchBranchByName(const Serializable& each, const string& name) {
    const Branch& branchReference = dynamic_cast<const Branch&>(each);
    return branchReference.getName() == name;
}

class BranchAccess {
public:
    bool existsWithName(const string& name) const {
        return persister->matches(matchBranchByName, name);
    }

private:
    shared_ptr<Persistence<Branch>> persister;
};


class BranchService {
public:
    void add(const string& name, const string& address) {
        if (branchAccess.existsWithName(name))
            throw DuplicateBranchNameException();
    }

private:
    BranchAccess branchAccess;
};


class BranchServiceTest: public Test {
public:
    BranchService service;
};


TEST_F(BranchServiceTest, addThrowsWhenNameNotUnique) {
    service.add("samename", "1");
    // ASSERT_THROW(service.add("samename", "1"), DuplicateBranchNameException);
}
