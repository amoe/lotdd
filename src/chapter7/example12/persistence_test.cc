#include <string>
#include <memory>
#include <gmock/gmock.h>

using std::string;
using testing::Test;
using testing::Eq;
using testing::NotNull;
using std::unique_ptr;
using std::make_unique;

class Serializable {
};

class TestSerializable: public Serializable {
public:
    TestSerializable(const string& name, const string& id): name(name), id(id) { }

    bool operator==(const TestSerializable& other) const {
        return other.name == name && other.id == id;
    }
    
private:
    string name;
    string id;
};


template <typename T>
class Persistence {
public:
    Persistence(const string& table): table(table) { }
    virtual ~Persistence(void) { }
    
    virtual void add(T&) = 0;
    virtual unique_ptr<T> get(const string& id) const = 0;

protected:
    string table;
};


template <typename T>
class KeyedMemoryPersistence: public Persistence<T> {
public:
    KeyedMemoryPersistence(const string& table): Persistence<T>(table) { }
    ~KeyedMemoryPersistence(void) { }

    virtual void add(T&) {
    }

    virtual unique_ptr<T> get(const string& id) const {
        return make_unique<T>(TestSerializable("foo", "bar"));
    }
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

// XXX: Should be using TEST_P macro
TEST_F(PersistenceTest, addedItemCanBeRetrievedById) {
    persister->add(*objectWithId1);
    auto found = persister->get("1");
    // bool foo = found == found;
    ASSERT_THAT(found, NotNull());
    ASSERT_THAT(*found, Eq(*objectWithId1));
}
