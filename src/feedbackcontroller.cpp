#include "feedbackcontroller.hpp"

FeedbackController::FeedbackController() {};

FeedbackController::FeedbackController(FCType type) {
    this->type = type;
};

FeedbackController::FeedbackController(double setpoint, FCType type) {
    this->setpoint = setpoint;
    this->type = type;
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
    if (fc.getSetpoint() != NULL) 
        strm << " with setpoint " << fc.getSetpoint() << "\n";
    else 
        strm << " undefined setpoint\n";
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