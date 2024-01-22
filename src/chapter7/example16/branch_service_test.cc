#include <string>
#include <gmock/gmock.h>
#include "branch.hh"
#include "persistence.hh"
#include "keyed_memory_persistence.hh"
#include "serializable.hh"

using testing::Test;
using testing::Eq;
using testing::Ne;
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

    void deleteAll() {
        persister->clear();
    }


private:
    shared_ptr<Persistence<Branch>> persister;
};


class BranchService {
public:
    string add(const string& name, const string& address) {
        if (branchAccess.existsWithName(name))
            throw DuplicateBranchNameException();

        string generatedId = to_string(branchAccess.size());
        Branch theBranch{generatedId, name};
        branchAccess.save(theBranch);
        return generatedId;
    }

    void add(Branch& branch) {
        branchAccess.save(branch);
    }

    int branchCount() const {
        return branchAccess.size();
    }

    static void deleteAll() {
        BranchAccess access;
        access.deleteAll();
    }

private:
    BranchAccess branchAccess;
};


class BranchServiceTest: public Test {
public:
    Branch* eastBranch;
    Branch* westBranch;
    BranchService service;

    void SetUp() override {
        BranchService::deleteAll();
        eastBranch = new Branch{"1", "east"};
        westBranch = new Branch{"2", "west"};
    }
};




TEST_F(BranchServiceTest, addThrowsWhenNameNotUnique) {
    service.add("samename", "1");
    ASSERT_THROW(service.add("samename", "1"), DuplicateBranchNameException);
}


// No need to catch exceptions here, so we don't.
TEST_F(BranchServiceTest, addGeneratesUniqueId) {
    string id1 = service.add("name1", "");
    string id2 = service.add("name2", "");
    ASSERT_THAT(id1, Ne(id2));
}

TEST_F(BranchServiceTest, addBranchIncrementsCount) {
    service.add(*eastBranch);
    ASSERT_THAT(service.branchCount(), Eq(1));
    service.add(*westBranch);
    ASSERT_THAT(service.branchCount(), Eq(2));
}

