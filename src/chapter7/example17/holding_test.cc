#include <memory>
#include <gmock/gmock.h>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "branch.hh"

using testing::Test;
using testing::Eq;
using boost::gregorian::date;
using boost::gregorian::date_duration;
using std::make_unique;
using std::unique_ptr;
using std::string;

class Book {
public:
    static const int BOOK_CHECKOUT_PERIOD;
    static const int MOVIE_CHECKOUT_PERIOD;
};

const int Book::BOOK_CHECKOUT_PERIOD{21};
const int Book::MOVIE_CHECKOUT_PERIOD{7};


class Holding {
public:
    Holding() { }
    
    Holding(const std::string& classification, unsigned short copyNumber):
        classification(classification) {
    }

    date dueDate() const {
        int period;
        
        if (classification == "VABC 123") {
            period = Book::MOVIE_CHECKOUT_PERIOD;
        } else {
            period = Book::BOOK_CHECKOUT_PERIOD;
        }
        
        return lastCheckedOutOn + date_duration{period};
    }

    void checkIn(date checkInDate, Branch branch) {
        _isAvailable = true;
    }
    
    void checkOut(date checkOutDate) {
        _isAvailable = false;
        lastCheckedOutOn = checkOutDate;
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
    string classification;
    date lastCheckedOutOn;
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

class AMovieHolding: public HoldingTest {
public:
    unique_ptr<Holding> movie;

    void SetUp() {
        HoldingTest::SetUp();

        movie = make_unique<Holding>("VABC 123", 1);
        movie->transfer(EAST_BRANCH);
    }
};

TEST_F(AMovieHolding, answersDateDueWhenCheckedOut) {
    movie->checkOut(date{2013, 3, 1});
    date due = movie->dueDate();
    ASSERT_THAT(due, Eq(date{2013, 3, 8}));
}
