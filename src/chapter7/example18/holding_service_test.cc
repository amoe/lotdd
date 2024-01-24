#include <string>
#include <gmock/gmock.h>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "branch.hh"
#include "classification_data.hh"

using testing::Test;
using testing::Eq;
using std::string;
using boost::gregorian::date;
using boost::gregorian::date_duration;

class Patron {
public:
    Patron() { }

    // Hardcoded to return 10 to avoid building out some of the fine
    // infrastructure.  As we're only trying to improve the format of the test,
    // not the system under test.
    int getFineBalance() const {
        return 10;
    }
};


class HoldingService {
public:
    void checkIn(const string& barcode, date checkInDate, const string& branchId) {
    }
};

class HoldingBarcode {
public:
    HoldingBarcode(string classification, int copyNumber) { }

    const string& toString() const {
        return classification;
    }

private:
    string classification;
};


class HoldingServiceTest: public Test {
public:
    Branch* branch1;
    Branch* branch2;
    date* arbitraryDate;
    HoldingService holdingService;

    void SetUp() {
        // No idea why these are pointers
        branch1 = new Branch("1", "branch1");
        branch2 = new Branch("2", "branch2");

        arbitraryDate = new date{2013, 1, 1};
    }

    void checkOut(const HoldingBarcode& barcode, Branch* branch, string patronCardNumber) {
        // TODO
    }

    Patron findPatronWithId(string id) {
        return Patron();
    }

};


TEST_F(HoldingServiceTest, X) {
    HoldingBarcode barcode(ClassificationData::THE_TRIAL_CLASSIFICATION, 1);
    string patronCardNumber{"p5"};
    checkOut(barcode, branch1, patronCardNumber);
    date_duration oneDayLate(Book::BOOK_CHECKOUT_PERIOD + 1);
    holdingService.checkIn(barcode.toString(), *arbitraryDate + oneDayLate, branch2->getId());
    ASSERT_THAT(
        findPatronWithId(patronCardNumber).getFineBalance(), Eq(Book::BOOK_DAILY_FINE)
    );
}
