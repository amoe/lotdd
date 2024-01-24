

#include "book.hh"

namespace ClassificationData {
    const std::string SEVEN_CLASSIFICATION = "VABC 123";

    const std::string SEVEN_AUTHOR = "Fincher";
    const unsigned short SEVEN_YEAR = 1995;
    const std::string SEVEN_TITLE = "Se7en";
    
    const Book SEVEN(SEVEN_TITLE, SEVEN_AUTHOR, SEVEN_YEAR, SEVEN_CLASSIFICATION, Book::TYPE_MOVIE);


    const std::string THE_TRIAL_TITLE = "Trial, The";
    const std::string THE_TRIAL_AUTHOR = "Kafka, Franz";
    const std::string THE_TRIAL_CLASSIFICATION = "PZ3.K11 Tr2";
    const unsigned short THE_TRIAL_YEAR = 1937;

    const Book THE_TRIAL(
        THE_TRIAL_TITLE, THE_TRIAL_AUTHOR, THE_TRIAL_YEAR, THE_TRIAL_CLASSIFICATION
    );
}
