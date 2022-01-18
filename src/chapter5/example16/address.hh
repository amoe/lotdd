#ifndef ADDRESS_HH
#define ADDRESS_HH

// forgive the US-centric nature of this.  It should be modified once we
// have more working tests.
struct Address {
    std::string road;
    std::string city;
    std::string state;
    std::string country;

    std::string summaryDescription() const {
        return road + ", " + city + ", " + state + ", " + country;
    }
};

#endif /* ADDRESS_HH */
