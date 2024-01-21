#include <string>
#include <memory>
#include <unordered_map>
#include <gmock/gmock.h>
#include "serializable.hh"
#include "persistence.hh"
#include "keyed_memory_persistence.hh"

using std::string;
using testing::Test;
using testing::Eq;
using testing::NotNull;
using testing::IsNull;
using testing::Pointee;
using std::unique_ptr;
using std::make_unique;
using std::unordered_map;

class TestSerializable: public Serializable {
public:
    TestSerializable(const string& name, const string& id): name(name), id(id) { }

    virtual string getId() const {
        return id;
    }

    bool operator==(const TestSerializable& other) const {
        return other.name == name && other.id == id;
    }
    
private:
    string name;
    string id;
};

class PersistenceTest: public Test {
public:
    Persistence<TestSerializable>* persister;
    TestSerializable* objectWithId1;

    void SetUp() override {
        // Modified from Langr's class to directly instantiate a persister
        // instead of using a factory and a parameterized test.
        persister = new KeyedMemoryPersistence<TestSerializable>{"table"};
        objectWithId1 = new TestSerializable{"one", "1"};
    }
};

// create 2 objects, 1 called persister
TEST_F(PersistenceTest, addedItemCanBeRetrievedById) {
    persister->add(*objectWithId1);
    auto found = persister->get("1");
    ASSERT_THAT(found, Pointee(*objectWithId1));
}

TEST_F(PersistenceTest, returnsNullPointerWhenItemNotFound) {
    ASSERT_THAT(persister->get("no id there"), IsNull());
}
