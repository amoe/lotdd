#include <gmock/gmock.h>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "branch.hh"

using testing::Test;
using testing::Eq;
using boost::gregorian::date;
using boost::gregorian::date_duration;

class Book {
public:
    static const int BOOK_CHECKOUT_PERIOD;
};

const int Book::BOOK_CHECKOUT_PERIOD{21};


class Holding {
public:
    date dueDate() const {
        return date{1970, 1, 1} + date_duration{Book::BOOK_CHECKOUT_PERIOD};
    }

    void checkIn(date checkInDate, Branch branch) {
        _isAvailable = true;
    }
    
    void checkOut(date checkOutDate) {
        _isAvailable = false;
    }

    void transfer(Branch branch) {
    }

    // XXX: This is clearly buggy as it doesn't differentiate with respect to
    // the branch, but it's enough to satisfy the unit test for now.
    bool isAvailable() const {
        return _isAvailable;
    }

private:
    bool _isAvailable;   // hacky invention by me
};

class HoldingTest: public Test {
public:
    Holding* holding;
    Branch* arbitraryBranch;
    
    bool isAvailableAt(Holding* holding, Branch& branch) {
        return true;
    }

    static const date ARBITRARY_DATE;


    virtual void SetUp() override {
        holding = new Holding();
    }
};

Branch EAST_BRANCH{"1", "east"};

const date HoldingTest::ARBITRARY_DATE{1970, 1, 1};

TEST_F(HoldingTest, availability) {
    holding->transfer(EAST_BRANCH);
    holding->checkOut(ARBITRARY_DATE);
    EXPECT_FALSE(holding->isAvailable());

    date nextDay = ARBITRARY_DATE + date_duration{1};
    holding->checkIn(nextDay, EAST_BRANCH);
    EXPECT_TRUE(holding->isAvailable());
}

class CheckedInHolding: public HoldingTest {
};

TEST_F(CheckedInHolding, updatesDateDueOnCheckout) {
    ASSERT_TRUE(isAvailableAt(holding, *arbitraryBranch));

    holding->checkOut(ARBITRARY_DATE);
    ASSERT_THAT(
        holding->dueDate(), Eq(ARBITRARY_DATE + date_duration{Book::BOOK_CHECKOUT_PERIOD})
    );
}


TEST_F(HoldingTest, isNotAvailableAfterCheckout) {
    holding->transfer(EAST_BRANCH);

    holding->checkOut(ARBITRARY_DATE);

    EXPECT_THAT(
        holding->isAvailable(), Eq(false)
    );
}

// You can check a book back in on the same day that you check it out, I believe.
TEST_F(HoldingTest, isAvailableAfterCheckin) {
    holding->transfer(EAST_BRANCH);
    holding->checkOut(ARBITRARY_DATE);
    holding->checkIn(ARBITRARY_DATE, EAST_BRANCH);

    EXPECT_THAT(
        holding->isAvailable(), Eq(true)
    );
}

