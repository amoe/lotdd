#include <string>
#include <gmock/gmock.h>
#include "branch.hh"

using testing::Test;
using testing::Eq;
using std::string;
using std::exception;

class BranchService {
public:
    void add(const string& name, const string& address) { }
};


class BranchServiceTest: public Test {
public:
    BranchService service;
};


class DuplicateBranchNameException: public exception {
};


TEST_F(BranchServiceTest, addThrowsWhenNameNotUnique) {
    service.add("samename", "1");
    ASSERT_THROW(service.add("samename", "1"), DuplicateBranchNameException);
}
