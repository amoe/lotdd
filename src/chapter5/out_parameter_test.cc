#include <gmock/gmock.h>

using namespace testing;

// Demonstrates mocking of out parameters.
// Taken from JL's errata.

class DifficultCollaborator {
public:
    virtual bool calculate(int* result) {
        throw 1;
    }
};

class Target {
public:
    int execute(DifficultCollaborator* calculator) {
        int i;
        if (calculator->calculate(&i)) {
            return i;
        } else {
            return 0;
        }
    }
};



class DifficultCollaboratorMock: public DifficultCollaborator {
public:
    MOCK_METHOD1(calculate, bool(int*));
};



TEST(OutParameterTest, ReturnAnAmountWhenCalculatePasses) {
    DifficultCollaboratorMock difficult;
    Target calc;

    EXPECT_CALL(difficult, calculate(_)).WillOnce(DoAll(SetArgPointee<0>(3), Return(true)));

    auto result = calc.execute(&difficult);
    ASSERT_THAT(result, Eq(3));
}

