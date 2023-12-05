#include <string>
#include <memory>
#include <unordered_map>
#include <gmock/gmock.h>
#include "serializable.hh"
#include "persistence.hh"

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


template <typename T>
class KeyedMemoryPersistence: public Persistence<T> {
public:
    KeyedMemoryPersistence(const string& table): Persistence<T>(table) { }
    ~KeyedMemoryPersistence(void) { }

    virtual void add(T& item) {
        contents.insert({item.getId(), item});
    }

    virtual unique_ptr<T> get(const string& id) const {
        auto it = contents.find(id);

        if (it == contents.end()) {
            return nullptr;
        } else {
            return make_unique<T>(contents.at(id));
        }
    }

    virtual bool matches(MatcherFunction matches, const string& name) const {
        for (const auto& pair: contents) {
            if (matches(pair.second, name))
                return true;
        }
        return false;
    }

private:
    unordered_map<string, T> contents;
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
