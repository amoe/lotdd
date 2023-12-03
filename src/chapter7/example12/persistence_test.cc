#include <string>
#include <gmock/gmock.h>

using std::string;
using testing::Test;
using testing::Eq;

template <typename T>
class Persistence {
public:
    Persistence(const string& table): table(table) { }
    virtual ~Persistence(void) { }
    
    virtual void add(T&) = 0;
    virtual T get(const string& id) const = 0;

protected:
    string table;
};

class Serializable {
};

class TestSerializable: public Serializable {
public:
    TestSerializable(const string& name, const string& id): name(name), id(id) { }

private:
    string name;
    string id;
};


class PersistenceTest: public Test {
public:
    Persistence<TestSerializable>* persister;
    TestSerializable* objectWithId1;

    void SetUp() override {
        // currently causing a compiler error: "invalid new-expression"
//        persister = new Persistence<TestSerializable>{};
        objectWithId1 = new TestSerializable{"one", "1"};
    }
};

// create 2 objects, 1 called persister

// XXX: Should be using TEST_P macro
TEST_F(PersistenceTest, addedItemCanBeRetrievedById) {
    persister->add(*objectWithId1);
//    auto found = persister->get("1");
}