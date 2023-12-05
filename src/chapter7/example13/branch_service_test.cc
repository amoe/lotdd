#include <string>
#include <gmock/gmock.h>
#include "branch.hh"
#include "persistence.hh"
#include "keyed_memory_persistence.hh"
#include "serializable.hh"

using testing::Test;
using testing::Eq;
using std::string;
using std::exception;
using std::shared_ptr;
using std::to_string;

class DuplicateBranchNameException: public exception {
};


bool matchBranchByName(const Serializable& each, const string& name) {
    const Branch& branchReference = dynamic_cast<const Branch&>(each);
    return branchReference.getName() == name;
}

class BranchAccess {
public:
    BranchAccess(): persister(new KeyedMemoryPersistence<Branch>("table")) { }
    
    bool existsWithName(const string& name) const {
        return persister->matches(matchBranchByName, name);
    }

    void save(Branch& branch) {
        persister->add(branch);
    }

    int size() const {
        return persister->size();
    }


private:
    shared_ptr<Persistence<Branch>> persister;
};


class BranchService {
public:
    void add(const string& name, const string& address) {
        if (branchAccess.existsWithName(name))
            throw DuplicateBranchNameException();

        string generatedId = to_string(branchAccess.size());
        Branch theBranch{generatedId, name};
        branchAccess.save(theBranch);
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
    ASSERT_THROW(service.add("samename", "1"), DuplicateBranchNameException);
}
