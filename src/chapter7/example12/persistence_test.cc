#include <gmock/gmock.h>

using testing::Test;
using testing::Eq;


class PersistenceTest: public Test {
};

// create 2 objects, 1 called persister


TEST_P(PersistenceTest, addedItemCanBeRetrievedById) {
    persister->add(*objectWithId1);
}
