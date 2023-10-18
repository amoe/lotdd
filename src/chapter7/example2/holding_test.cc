#include <gmock/gmock.h>
#include <boost/date_time/gregorian/gregorian_types.hpp>


using testing::Test;
using testing::Eq;
using boost::gregorian::date;
using boost::gregorian::date_duration;

class Book {
public:
    static const int BOOK_CHECKOUT_PERIOD;
};

const int Book::BOOK_CHECKOUT_PERIOD{21};

class Branch {
};

class Holding {
public:
    date dueDate() const {
        return date{1970, 1, 1} + date_duration{Book::BOOK_CHECKOUT_PERIOD};
    }
    
    void checkOut(date checkOutDate) {
    }
};

class HoldingTest: public Test {
public:
    Holding* holding;
    Branch* arbitraryBranch;
    
    bool isAvailableAt(Holding* holding, Branch& branch) {
        return true;
    }

    static const date ARBITRARY_DATE;
};

const date HoldingTest::ARBITRARY_DATE{1970, 1, 1};

class CheckedInHolding: public HoldingTest {
};

TEST_F(CheckedInHolding, updatesDateDueOnCheckout) {
    ASSERT_TRUE(isAvailableAt(holding, *arbitraryBranch));

    holding->checkOut(ARBITRARY_DATE);
    ASSERT_THAT(
        holding->dueDate(), Eq(ARBITRARY_DATE + date_duration{Book::BOOK_CHECKOUT_PERIOD})
    );
}

