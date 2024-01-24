#include "classification_service.hh"
#include "classification_data.hh"

Book ClassificationService::retrieveDetails(const string& classification) const {
    if (classification == ClassificationData::SEVEN_CLASSIFICATION) {
        return ClassificationData::SEVEN;
    } else if (classification == ClassificationData::THE_TRIAL_CLASSIFICATION) {
        return ClassificationData::THE_TRIAL;
    } else {
        throw ClassificationNotFoundException(classification);
    }
}
