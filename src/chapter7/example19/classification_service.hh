#include <string>
#include <stdexcept>
#include "book.hh"

using std::string;
using std::runtime_error;

class ClassificationService {
public:
    Book retrieveDetails(const string& classification) const;
};


// Derive from runtime_error, but store the classification that failed inside
// a data member of the class.
class ClassificationNotFoundException: public std::runtime_error {
public:
    ClassificationNotFoundException(
        const std::string& classification
    ): std::runtime_error("classification not found"),
       classification(classification) { }

private:
    std::string classification;
};
