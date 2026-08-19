#ifndef FEEDBACKCONTROLLER_HPP
#define FEEDBACKCONTROLLER_HPP

#include <sstream>

enum FCType {
    PID
};

class FeedbackController {
    public:
        FeedbackController();
        FeedbackController(double setpoint);

        virtual double loop(double input) = 0;
        virtual void init() = 0;

        double getSetpoint();
        double getSetpoint() const;
        void setSetpoint(double setpoint);

        friend std::ostream& operator<<(std::ostream &strm, const FeedbackController& fc);

    private:
        FCType type;

        const char* getTypeAsString();
        const char* getTypeAsString() const;

        double setpoint;
};

#endif