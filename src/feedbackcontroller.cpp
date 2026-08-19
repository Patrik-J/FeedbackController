#include "feedbackcontroller.hpp"

FeedbackController::FeedbackController() {};

FeedbackController::FeedbackController(double setpoint) {
    this->setpoint = setpoint;
};

double FeedbackController::getSetpoint() {
    return this->setpoint;
};

double FeedbackController::getSetpoint() const {
    return this->setpoint;
};

void FeedbackController::setSetpoint(double setpoint) {
    this->setpoint = setpoint;
};

std::ostream& operator<<(std::ostream& strm, const FeedbackController& fc) {
    strm << "Feedback Controller of type " << fc.getTypeAsString();
    strm << " with setpoint " << fc.getSetpoint() << "\n";
    return strm;
};

const char* FeedbackController::getTypeAsString() {
    switch(this->type) {
        case PID:
            return "PID";
        default:
            return "Unknown";
    }
};

const char* FeedbackController::getTypeAsString() const {
    switch(this->type) {
        case PID:
            return "PID";
        default:
            return "Unknown";
    }
};